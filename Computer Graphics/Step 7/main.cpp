﻿// Step 2 Vector.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "resource.h"
#include "MathUtil.h"
#include <mmsystem.h>
#include <objidl.h>
#include <gdiplus.h>
#include <cmath>
#include "Matrix3D.h"
#include "Polygon.h"

using namespace Gdiplus;

#pragma comment(lib, "winmm.lib")
#pragma comment (lib,"Gdiplus.lib")

enum class AnimationMode
{
	
	eRotate_AnimMode = 0,
	eShear_AnimMode,
	eNot_AnimMode,
};

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HWND g_Hwnd;
HDC g_hdc;
HBITMAP g_hBitmap = 0;
RECT g_ClientRect;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Initialize();
void Finalize();
// 윈도우 사이즈 변경시, Proc에서 OnSize를 호출하여, 숨겨진 버퍼의 정보를 갱신함.
void OnSize();
// OnIdle의 그리기 루틴은 모두 숨겨진 버퍼에 적용됨.
// 숨겨진 버퍼의 내용은 전면 버퍼에 복사함.
// DirectX 의 Flipping 보다 느리지만 Flickering은 발생하지 않음.
void OnIdle(float fElapsedTime);

void OnRender(HDC, float);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_STEP2VECTOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STEP2VECTOR));

	Initialize();
	DWORD dwOldTime = timeGetTime();

    MSG msg;

    // 기본 메시지 루프입니다:
    while (true)
    {
		::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
		const DWORD dwNewTime = timeGetTime();
		const BOOL bIsTranslateMessage = TranslateAccelerator(msg.hwnd, hAccelTable, &msg);

		if (!bIsTranslateMessage)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		OnIdle(float(dwNewTime - dwOldTime) / 1000.0f);
		Sleep(10);

		dwOldTime = dwNewTime;

		if (msg.message == WM_QUIT)
			break;
    }

	Finalize();
	GdiplusShutdown(gdiplusToken);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STEP2VECTOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_STEP2VECTOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_Hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_Hwnd)
   {
      return FALSE;
   }

   ShowWindow(g_Hwnd, nCmdShow);
   UpdateWindow(g_Hwnd);

   return TRUE;
}

void OnPaint(HDC& hdc)
{
	Graphics graphics(hdc);
	Pen      pen(Color(255, 0, 0, 255));
	graphics.DrawLine(&pen, 0, 0, 200, 100);
}

//

//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			// OnPaint(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_SIZE:
		OnSize();
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void Initialize()
{}

void Finalize()
{
	if (g_hdc != 0)
	{
		DeleteDC(g_hdc);
		g_hdc = 0;
	}

	if (g_hBitmap != 0)
	{
		DeleteObject(g_hBitmap);
		g_hBitmap = 0;
	}
}

void OnSize()
{
	// 현재 윈도우 DC와 호환되는 DC를 생성하고,  g_hdc에 넣음.
	// 이 DC에 비트맵 할당함.
	Finalize();

	GetClientRect(g_Hwnd, &g_ClientRect);
	const int iWidth = g_ClientRect.right - g_ClientRect.left + 1;
	const int iHeight = g_ClientRect.bottom - g_ClientRect.top + 1;

	MathUtil::Vector2D origin;
	origin.set_x(iWidth / 2.0f);
	origin.set_y(iHeight / 2.0f);
	MathUtil::g_screenCoordinate.SetInfo(MathUtil::Vector2D(50, 0),
		MathUtil::Vector2D(0, -50), origin);

	HDC hdc = GetDC(g_Hwnd);
	g_hdc = CreateCompatibleDC(hdc);
	g_hBitmap = CreateCompatibleBitmap(hdc, iWidth, iHeight);
	SelectObject(g_hdc, g_hBitmap);
}

void OnIdle(float fElapsedTime)
{
	using namespace MathUtil;

	const int iWidth = g_ClientRect.right - g_ClientRect.left + 1;
	const int iHeight = g_ClientRect.bottom - g_ClientRect.top + 1;

	HDC hdc = ::GetDC(g_Hwnd);

	OnRender(hdc, fElapsedTime);
	return;

	HBRUSH brush;
	brush = CreateSolidBrush(RGB(255, 255, 255));
	HGDIOBJ oldBrush = SelectObject(g_hdc, brush);
	Rectangle(g_hdc, 0, 0, iWidth, iHeight);

	
	BitBlt(hdc, 0, 0, iWidth, iHeight, g_hdc, 0, 0, SRCCOPY);
	SelectObject(g_hdc, oldBrush);
	DeleteObject(brush);

	::ReleaseDC(g_Hwnd, hdc);
}

void OnRender(HDC hdc, float fElapsedTime)
{
	using namespace MathUtil;

	DrawGrid(hdc, 30, 30);
	DrawAxis(hdc, 32, 32);

	MathUtil::Polygon polygon;
	polygon.SetIndexBuffer();
	polygon.SetVertexBuffer();

	polygon.Render(hdc);
}