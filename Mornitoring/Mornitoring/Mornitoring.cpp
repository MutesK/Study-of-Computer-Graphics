// Mornitoring.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Mornitoring.h"
#include "GraphUnit.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING] = L"Mornitor";                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING] = L"Mornitor";            // 기본 창 클래스 이름입니다.


CGraphUnit *p1;
CGraphUnit *p2;
CGraphUnit *p3;
CGraphUnit *p4;
CGraphUnit *p5;

bool Alert = false;
// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

    // TODO: 여기에 코드를 입력합니다.
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    MSG msg;

    // 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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
		p1->SetInformation(L"네트워크", L"Mbps", BRIGHTGRAY, DARKGRAY, 90, 100);
		p1->AddColumn(L"C1", WHITE, 1);
		

		p2 = new CGraphUnit(hInst, hWnd, CGraphUnit::LINE_MULTI, 10, 220, 810, 300);
		p2->SetInformation(L"서버 상황",  nullptr, BRIGHTGRAY, DARKGRAY, 90, 100);
		p2->AddColumn(L"개체 1", YELLOW, 0);
		p2->AddColumn(L"개체 2", GREEN, 0);
		p2->AddColumn(L"개체 3", PINK, 0);
		p2->AddColumn(L"개체 4", BLUE, 0);

		p3 = new CGraphUnit(hInst, hWnd, CGraphUnit::BAR_SINGLE_HORZ, 220, 10, 200, 200);
		p3->SetInformation(L"CPU", L"%", BRIGHTGRAY, DARKGRAY, 90, 100);
		p3->AddColumn(L"개체 1", NGREEN, 0);
		
		p4 = new CGraphUnit(hInst, hWnd, CGraphUnit::BAR_COLUMN_HORZ, 10, 550, 700, 200);
		p4->SetInformation(L"DB 버퍼", nullptr, BRIGHTGRAY, DARKGRAY, 90, 100);
		p4->AddColumn(L"개체 1", NGREEN, 0);
		p4->AddColumn(L"개체 2", NGREEN, 0);
		p4->AddColumn(L"개체 3", NGREEN, 0);
		p4->AddColumn(L"개체 4", NGREEN, 0);
		p4->AddColumn(L"개체 5", NGREEN, 0);
		p4->AddColumn(L"개체 6", NGREEN, 0);


		p5 = new CGraphUnit(hInst, hWnd, CGraphUnit::PIE, 900, 220, 400, 400);
		p5->SetInformation(L"파이 차트", nullptr, BRIGHTGRAY, DARKGRAY, 100, 100);
		p5->AddColumn(L"개체 1", YELLOW, 0);
		p5->AddColumn(L"개체 2", GREEN, 0);
		p5->AddColumn(L"개체 3", PINK, 0);
		p5->AddColumn(L"개체 4", BLUE, 0);


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
			// 경고
			isAlert = false;
			KillTimer(hWnd, 2);
			InvalidateRect(hWnd, NULL, true);
			break;
		}
		break;
	case UM_ALERT:
		// 화면을 빨갛게 점멸한다.
		SetTimer(hWnd, 2, 1000, NULL);
		isAlert = true;
		InvalidateRect(hWnd, NULL, true);
		break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

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