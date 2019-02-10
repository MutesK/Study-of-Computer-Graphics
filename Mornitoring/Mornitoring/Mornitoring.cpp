// Mornitoring.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Mornitoring.h"
#include "GraphUnit.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING] = L"Mornitor";                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING] = L"Mornitor";            // �⺻ â Ŭ���� �̸��Դϴ�.


CGraphUnit *p1;
CGraphUnit *p2;
CGraphUnit *p3;
CGraphUnit *p4;
CGraphUnit *p5;

bool Alert = false;
// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    ParentWndProc(HWND, UINT, WPARAM, LPARAM);
int getRand();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
    while (true)
    {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
    }

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = ParentWndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
	wcex.hIcon = NULL;
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = NULL;

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK ParentWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool isAlert = false;

    switch (message)
    {
	case WM_CREATE:
	{
		
		p1 = new CGraphUnit(hInst, hWnd, CGraphUnit::LINE_SINGLE, 10, 10, 200, 200);
		p1->SetInformation(L"��Ʈ��ũ", L"Mbps", BRIGHTGRAY, DARKGRAY, 90, 100);
		p1->AddColumn(L"C1", WHITE, 1);
		

		p2 = new CGraphUnit(hInst, hWnd, CGraphUnit::LINE_MULTI, 10, 220, 810, 300);
		p2->SetInformation(L"���� ��Ȳ",  nullptr, BRIGHTGRAY, DARKGRAY, 90, 100);
		p2->AddColumn(L"��ü 1", YELLOW, 0);
		p2->AddColumn(L"��ü 2", GREEN, 0);
		p2->AddColumn(L"��ü 3", PINK, 0);
		p2->AddColumn(L"��ü 4", BLUE, 0);

		p3 = new CGraphUnit(hInst, hWnd, CGraphUnit::BAR_SINGLE_HORZ, 220, 10, 200, 200);
		p3->SetInformation(L"CPU", L"%", BRIGHTGRAY, DARKGRAY, 90, 100);
		p3->AddColumn(L"��ü 1", NGREEN, 0);
		
		p4 = new CGraphUnit(hInst, hWnd, CGraphUnit::BAR_COLUMN_HORZ, 10, 550, 700, 200);
		p4->SetInformation(L"DB ����", nullptr, BRIGHTGRAY, DARKGRAY, 90, 100);
		p4->AddColumn(L"��ü 1", NGREEN, 0);
		p4->AddColumn(L"��ü 2", NGREEN, 0);
		p4->AddColumn(L"��ü 3", NGREEN, 0);
		p4->AddColumn(L"��ü 4", NGREEN, 0);
		p4->AddColumn(L"��ü 5", NGREEN, 0);
		p4->AddColumn(L"��ü 6", NGREEN, 0);


		p5 = new CGraphUnit(hInst, hWnd, CGraphUnit::PIE, 900, 220, 400, 400);
		p5->SetInformation(L"���� ��Ʈ", nullptr, BRIGHTGRAY, DARKGRAY, 100, 100);
		p5->AddColumn(L"��ü 1", YELLOW, 0);
		p5->AddColumn(L"��ü 2", GREEN, 0);
		p5->AddColumn(L"��ü 3", PINK, 0);
		p5->AddColumn(L"��ü 4", BLUE, 0);


		SetTimer(hWnd, 1, 1000, NULL);
	}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			
			p1->InsertData(0, 0, getRand());
			
			p2->InsertData(0, 0, getRand());
			p2->InsertData(1, 0, getRand());
			p2->InsertData(2, 0, getRand());
			p2->InsertData(3, 0, getRand());

			p3->InsertData(0, 0, getRand());
			
			p4->InsertData(0, 0, getRand());
			p4->InsertData(1, 0, getRand());
			p4->InsertData(2, 0, getRand());
			p4->InsertData(3, 0, getRand());
			p4->InsertData(4, 0, getRand());
			p4->InsertData(5, 0, getRand());

			p5->InsertData(0, 0, getRand());
			p5->InsertData(1, 0, getRand());
			p5->InsertData(2, 0, getRand());
			p5->InsertData(3, 0, getRand());

			break;
		case 2:
			// ���
			isAlert = false;
			KillTimer(hWnd, 2);
			InvalidateRect(hWnd, NULL, true);
			break;
		}
		break;
	case UM_ALERT:
		// ȭ���� ������ �����Ѵ�.
		SetTimer(hWnd, 2, 1000, NULL);
		isAlert = true;
		InvalidateRect(hWnd, NULL, true);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.

			RECT rect;
			GetClientRect(hWnd, &rect);

			HBRUSH backColor, oldColor;
			if(isAlert)
				backColor = CreateSolidBrush(RED);
			else 
				backColor = CreateSolidBrush(BLACK);

			oldColor = (HBRUSH)SelectObject(hdc, backColor);
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

			SelectObject(hdc, oldColor);
			DeleteObject(backColor);

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


int getRand()
{

	int randvalue = (rand() % 95);
	
	return randvalue;
}