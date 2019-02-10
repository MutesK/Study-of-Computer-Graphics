#include "stdafx.h"
#include "GraphUnit.h"

int Windowcount = 0;

CGraphUnit::CGraphUnit(HINSTANCE hInstance, HWND hWndParent, TYPE type, int posX, 
	int posY, int width, int height)
	:m_hWndParent(hWndParent), m_type(type)
{

	// 윈도우 구조체 설정
	WNDCLASSEXW wcex;
	wsprintf(m_className, L"%d_MonitorGraph", Windowcount);

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	// 확장영역 sizeof(this) this값을 넣는다. 그래서 Handle(hWnd)를 통해 가져온다.
	wcex.cbWndExtra = sizeof(this); 

	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_className;
	wcex.hIconSm = NULL;

	RegisterClassExW(&wcex);
	
	m_hWnd = CreateWindow(m_className, NULL, WS_CHILD | WS_VISIBLE ,// WS_CAPTION | WS_CLIPSIBLINGS,
		posX, posY, width, height, hWndParent, NULL, hInstance, NULL);

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	SetWindowLongPtr(m_hWnd, 0, (LONG_PTR)this); // GetWindowLongPtr로 가져온다.

	ComponentSetting();
}


CGraphUnit::~CGraphUnit()
{

}
LRESULT CALLBACK CGraphUnit::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CGraphUnit *pThis = nullptr;
	PAINTSTRUCT ps;
	HDC hdc;

	pThis = (CGraphUnit *)GetWindowLongPtr(hWnd, 0);

	if(pThis == nullptr)
		return DefWindowProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_TIMER:
		pThis->m_alert = false;
		KillTimer(hWnd, 0);
		break;
	case WM_PAINT:
	{		
		hdc = BeginPaint(hWnd, &ps);

		switch (pThis->m_type)
		{
			case LINE_SINGLE:
				pThis->Draw_LINESINGLE();
				break;
			case BAR_SINGLE_HORZ:
				pThis->Draw_BARSINGLEHORZ();
				break;
			case LINE_MULTI:
				pThis->Draw_LINEMULTI();
				break;
			case BAR_COLUMN_HORZ:
				pThis->Draw_BARCOLUMNHORZ();
				break;
			case PIE:
				pThis->Draw_PIE();
				break;
				
		}
		pThis->FilpDC(hdc);
		ReleaseDC(hWnd, hdc);
		EndPaint(hWnd, &ps);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
// ===========================================================
// 기본 설정을 하는 함수.
// ===========================================================
void CGraphUnit::ComponentSetting()
{
	HDC hdc = GetDC(m_hWnd);
	GetClientRect(m_hWnd, &m_ClientRect);

	m_hMemDc = CreateCompatibleDC(hdc);
	m_hMemBitMap = CreateCompatibleBitmap(hdc, m_ClientRect.right, m_ClientRect.bottom);

	m_hOldMemBitMap = (HBITMAP)SelectObject(m_hMemDc, m_hMemBitMap);

	ReleaseDC(m_hWnd, hdc);
	PatBlt(m_hMemDc, 0, 0, m_ClientRect.right, m_ClientRect.bottom, WHITENESS);

	m_titleRect.top = 0;
	m_titleRect.left = 0;
	m_titleRect.right = m_ClientRect.right;
	m_titleRect.bottom = dfWindowTitle_HEIGHT;

	m_graphRect.top = dfWindowTitle_HEIGHT ;
	m_graphRect.left = 0;
	m_graphRect.right = m_ClientRect.right;
	m_graphRect.bottom = m_ClientRect.bottom;
	
	m_titlePEN = CreatePen(PS_SOLID, 1, BLACK);
	m_gridPen = CreatePen(PS_SOLID, 1, VBRIGHTGRAY);
	m_titleFont = CreateFont(TITLEFONT_HEIGHT, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0, L"맑은 고딕");
	m_girdFont = CreateFont(GRIDFONT_HEIGHT, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0, L"맑은 고딕");
	
	ServerID = 0;
}

// ===========================================================
// TITLE 출력 함수
// ===========================================================
void CGraphUnit::Draw_TITLE()
{
	SelectObject(m_hMemDc, m_titleBackColor);
	SelectObject(m_hMemDc, m_titlePEN);
	Rectangle(m_hMemDc, m_titleRect.left, m_titleRect.top, m_titleRect.right, m_titleRect.bottom);
}

void CGraphUnit::Single_DrawSetting(int _ColumnWidth, int _ColumnHeight)
{
	PatBlt(m_hMemDc, 0, 0, m_ClientRect.right, m_ClientRect.bottom, WHITENESS);

	Draw_TITLE();

	// 그래프 외곽 선작업
	SelectObject(m_hMemDc, m_titlePEN);
	SelectObject(m_hMemDc, m_graphBackColor);
	Rectangle(m_hMemDc, m_graphRect.left, m_graphRect.top, m_graphRect.right, m_graphRect.bottom);

	// 그래프 그리드 선 작업
	SelectObject(m_hMemDc, m_gridPen);
	SetTextColor(m_hMemDc, WHITE);
	int gridLineCnt = abs((m_graphRect.bottom - _ColumnHeight) - m_graphRect.top) / 4;
	int gridY = gridLineCnt;
	for (int i = 1; i < 4; i++)
	{
		MoveToEx(m_hMemDc, 1, m_graphRect.bottom - gridLineCnt - _ColumnHeight, NULL);
		LineTo(m_hMemDc, m_graphRect.right - _ColumnWidth - 1, m_graphRect.bottom - gridLineCnt - _ColumnHeight);

		gridLineCnt += gridY;
	}

	// 그래프 그리드 수치 작업
	int PosY = 0;
	int index = 0;
	while (m_info->queue.Peek(&PosY, index))
	{
		if (m_maxValue < PosY)
			m_maxValue = PosY;

		index++;
	}

	
	SelectObject(m_hMemDc, m_gridPen);
	SelectObject(m_hMemDc, m_girdFont);
	gridLineCnt = gridY;
	int indicatorValue = m_maxValue / 4;
	for (int i = 1; i <= 4; i++)
	{
		WCHAR wfValue[10];
		wsprintf(wfValue, L"%d", indicatorValue);
		TextOut(m_hMemDc, 5, m_graphRect.bottom - gridLineCnt + 5 - _ColumnHeight, wfValue, lstrlenW(wfValue) + 1);
		gridLineCnt += gridY;
		indicatorValue += m_maxValue / 4;
	}


}
// ===========================================================
// LINE_SINGLE 그리는 함수
// ===========================================================
void CGraphUnit::Draw_LINESINGLE()
{
	Single_DrawSetting(0 ,0);

	
	int index = 0;
	int PosY = 0, PosX = 0;
	int width = m_graphRect.right;
	int height = abs(m_graphRect.top - m_graphRect.bottom);

	int xCnt = ceil(width / (QUEUE_DATAMAX - 2));

	PosX = xCnt;
	// 그래프 그리프
	SelectObject(m_hMemDc, m_graphLine[0]);
	for (int i = 0; i < QUEUE_DATAMAX; i++)
	{
		if (m_info->queue.Peek(&PosY, index))
		{
			int value = reSetPosY(m_maxValue, height, PosY);
			if (index == 0)
				MoveToEx(m_hMemDc, PosX, m_ClientRect.bottom - value, NULL);
			else
				LineTo(m_hMemDc, PosX, m_ClientRect.bottom - value);

			
			index++;
			PosX += xCnt;
		}
		else
		{
			break;
		}
	}


	// 타이틀 
	WCHAR strTitle[45];
	wsprintf(strTitle, L"%s : %d %s", m_titleName, PosY, m_Unit);
	SetBkMode(m_hMemDc, TRANSPARENT);
	SetTextAlign(m_hMemDc, TA_TOP | TA_LEFT);

	SelectObject(m_hMemDc, m_titleFont);
	if (!m_alert)
		SetTextColor(m_hMemDc, WHITE);
	else
		SetTextColor(m_hMemDc, RED);

	TextOut(m_hMemDc, 10, 15, strTitle, lstrlenW(strTitle));

}

// ===========================================================
// LINE_MULTI 그리는 함수
// ===========================================================
void CGraphUnit::Draw_LINEMULTI()
{
	RECT ColumnRect;
	ColumnRect.bottom = m_ClientRect.bottom;
	ColumnRect.top = m_graphRect.top;
	ColumnRect.right = m_ClientRect.right;
	ColumnRect.left = m_ClientRect.right - (m_ClientRect.right / 6);
	

	// 그리기
	int index = 0;
	int PosY = 0, PosX = 0;
	int length = (m_ClientRect.right - m_ClientRect.right / 6);
	int height = abs(m_graphRect.top - m_graphRect.bottom);

	int xCnt = ceil(length / (QUEUE_DATAMAX - 1));
	Single_DrawSetting(m_ClientRect.right - xCnt * (QUEUE_DATAMAX - 1), 0);

	for (int i = 0; i <= ServerID; i++)
	{
		SelectObject(m_hMemDc, m_graphLine[i]);
		while (m_info[i].queue.Peek(&PosY, index))
		{
			int value = reSetPosY(m_maxValue, height, PosY);
			if (index == 0)
				MoveToEx(m_hMemDc, PosX, m_ClientRect.bottom - value, NULL);
			else
				LineTo(m_hMemDc, PosX, m_ClientRect.bottom - value);

			
			index++;
			PosX += xCnt;
		}

		PosX = xCnt;
		index = 0;
	}

	height = ColumnRect.bottom - ColumnRect.top;
	length = ColumnRect.right - ColumnRect.left;
	int yGap = 7;
	xCnt = length / 10;
	int yCnt = (height / 15) + yGap;
	PosX = ColumnRect.left + xCnt;
	PosY = ColumnRect.top + yCnt;
	for (int i = 0; i < ServerID; i++)
	{
		SelectObject(m_hMemDc, m_graphLine[i]);
		SelectObject(m_hMemDc, m_graphBarColor[i]);
		Rectangle(m_hMemDc, PosX, PosY, PosX + xCnt,  PosY - yGap);

		SelectObject(m_hMemDc, m_titlePEN);
		SetTextAlign(m_hMemDc, TA_TOP | TA_LEFT);
		TextOut(m_hMemDc, PosX + (xCnt * 2), PosY - (yGap) - 3, m_info[i].szName, lstrlenW(m_info[i].szName));

		PosY += yGap + 10;
	}

	

	// 타이틀 
	SetBkMode(m_hMemDc, TRANSPARENT);
	SetTextAlign(m_hMemDc, TA_TOP | TA_LEFT);

	SelectObject(m_hMemDc, m_titleFont);
	if (!m_alert)
		SetTextColor(m_hMemDc, WHITE);
	else
		SetTextColor(m_hMemDc, RED);

	TextOut(m_hMemDc, 10, 15, m_titleName, lstrlenW(m_titleName));

}

void CGraphUnit::Draw_BARSINGLEHORZ()
{
	Single_DrawSetting(0,0);

	RECT Bar;

	Bar.left = m_graphRect.right / 4;
	Bar.right = m_graphRect.right / 4 * 3;
	Bar.bottom = m_graphRect.bottom;

	int value = 0;
	int size = m_info->queue.getSize();
	m_info->queue.Peek(&value, size - 1);

	Bar.top = reSetPosY(m_maxValue, abs(Bar.bottom - m_graphRect.top), value);


	SelectObject(m_hMemDc, m_graphLine[0]);
	SelectObject(m_hMemDc, m_graphBarColor[0]);
	Rectangle(m_hMemDc, Bar.left, Bar.bottom - Bar.top, Bar.right, Bar.bottom);


	SetTextAlign(m_hMemDc, TA_TOP | TA_CENTER);
	SelectObject(m_hMemDc, m_titlePEN);
	int Xpos = (Bar.left + Bar.right) / 2;
	int Ypos = Bar.bottom - Bar.top  <= Bar.bottom - 30 ? Bar.bottom - Bar.top + 15 : Bar.bottom - 20;

	WCHAR szNum[30];
	wsprintf(szNum, L"%d", value);
	TextOut(m_hMemDc, Xpos, Ypos, szNum, lstrlenW(szNum));


	SetTextAlign(m_hMemDc, TA_TOP | TA_LEFT);
	// 타이틀 
	WCHAR strTitle[45];
	wsprintf(strTitle, L"%s : %d %s", m_titleName, value, m_Unit);
	SetBkMode(m_hMemDc, TRANSPARENT);
	SetTextAlign(m_hMemDc, TA_TOP | TA_LEFT);

	SelectObject(m_hMemDc, m_titleFont);
	if (!m_alert)
		SetTextColor(m_hMemDc, WHITE);
	else
		SetTextColor(m_hMemDc, RED);

	TextOut(m_hMemDc, 10, 15, strTitle, lstrlenW(strTitle));
}

void CGraphUnit::Draw_BARCOLUMNHORZ()
{
	Single_DrawSetting(0, 30);

	SetBkMode(m_hMemDc, TRANSPARENT);
	SelectObject(m_hMemDc, m_titleFont);
	if (!m_alert)
		SetTextColor(m_hMemDc, WHITE);
	else
		SetTextColor(m_hMemDc, RED);
	SetTextAlign(m_hMemDc, TA_TOP | TA_LEFT);
	SelectObject(m_hMemDc, m_titleFont);
	TextOut(m_hMemDc, 10, 15, m_titleName, lstrlenW(m_titleName));
	
	int GridGap = 30;
	int barGap = 5;
	
	int length = m_graphRect.right - 2 * GridGap;

	int barWidth = ((m_ClientRect.right - 60) / ServerID) - barGap;
	int Xpos = GridGap;
	int xGap = barGap;	// x값 증가량

	for (int i = 0; i < ServerID; i++)
	{
		RECT rect;

		rect.bottom = m_graphRect.bottom - 30;
		rect.left = Xpos;
		rect.right = Xpos + barWidth;

		int value = 0;
		int size = m_info[i].queue.getSize();
		m_info[i].queue.Peek(&value, size - 1);

		rect.top = reSetPosY(m_maxValue, abs(rect.bottom - m_graphRect.top), value);

		SelectObject(m_hMemDc, m_graphLine[i]);
		SelectObject(m_hMemDc, m_graphBarColor[i]);
		Rectangle(m_hMemDc, rect.left, rect.bottom - rect.top, rect.right, rect.bottom);

		SetTextAlign(m_hMemDc, TA_TOP | TA_CENTER);
		SelectObject(m_hMemDc, m_girdFont);
		int TextX = (rect.left + rect.right) / 2;
		int TextY = rect.bottom - rect.top  <= rect.bottom - 30  ? rect.bottom - rect.top + 15 : rect.bottom - 20;


		if (m_alertValue >= value)
			SetTextColor(m_hMemDc, WHITE);
		else
			SetTextColor(m_hMemDc, RED);

		WCHAR szNum[30];
		wsprintf(szNum, L"%d", value);
		TextOut(m_hMemDc, TextX,  TextY, szNum, lstrlenW(szNum));


		SelectObject(m_hMemDc, m_gridPen);
		TextOut(m_hMemDc, TextX, m_ClientRect.bottom - 30, m_info[i].szName, lstrlenW(m_info[i].szName));


		Xpos = rect.right + barGap;

	}
	SetTextColor(m_hMemDc, WHITE);
	SetTextAlign(m_hMemDc, TA_TOP | TA_LEFT);

}


void CGraphUnit::Draw_PIE()
{
	// 외곽 선작업
	PatBlt(m_hMemDc, 0, 0, m_ClientRect.right, m_ClientRect.bottom, WHITENESS);

	Draw_TITLE();
	SetBkMode(m_hMemDc, TRANSPARENT);
	SetTextColor(m_hMemDc, WHITE);
	SelectObject(m_hMemDc, m_titleFont);
	SetTextAlign(m_hMemDc, TA_TOP | TA_LEFT);
	TextOut(m_hMemDc, 10, 15, m_titleName, lstrlenW(m_titleName));

	SelectObject(m_hMemDc, m_titlePEN);
	SelectObject(m_hMemDc, m_graphBackColor);
	Rectangle(m_hMemDc, m_graphRect.left, m_graphRect.top, m_graphRect.right, m_graphRect.bottom);

	int divLength = m_graphRect.right / 10;

	RECT columnRect;
	columnRect.bottom = m_graphRect.bottom;
	columnRect.top = m_titleRect.bottom;
	columnRect.left = m_ClientRect.right - (divLength * 2);
	columnRect.right = m_ClientRect.right;


	//////////////////////////////////////////////////////////////////////////////////////////////
	// 지름
	int iCnt;
	int diameter = (abs(m_graphRect.left - columnRect.left)) - 30;
	
	int GraphDrawX = 15;
	int GraphDrawY = m_graphRect.top + ((m_graphRect.bottom - m_graphRect.top) - (m_graphRect.top + diameter));

	int midX = GraphDrawX + diameter / 2;
	int midY = GraphDrawY+ diameter / 2;
	// 시작점
	int iX = diameter, iY = diameter / 2;
	// 끝점
	int dX = iX, dY = iY;

	double AccRadian = 0; // 누적 라디안
	int Percent = 0;
	int totalData = 0;

	for (iCnt = 0; iCnt< ServerID; iCnt++)
	{
		int value = 0;
		int size = m_info[iCnt].queue.getSize();
		m_info[iCnt].queue.Peek(&value, size - 1);

		totalData += value;
	}

	for (iCnt = 0; iCnt < ServerID; iCnt++)
	{
		int value = 0;
		int size = m_info[iCnt].queue.getSize();
		m_info[iCnt].queue.Peek(&value, size - 1);

		if (value == 0)
			continue;

		double radian = value * 6.2831 / totalData;
		AccRadian += radian;
		
		iX = diameter / 2 + (int)(cos(AccRadian) * 100);
		iY = diameter / 2 + (int)(sin(AccRadian) * 100);



		SelectObject(m_hMemDc, m_graphLine[iCnt]);
		SelectObject(m_hMemDc, m_graphBarColor[iCnt]);
		Pie(m_hMemDc, GraphDrawX, GraphDrawY, GraphDrawX + diameter, GraphDrawY + diameter,
			GraphDrawX + iX, GraphDrawY + iY, GraphDrawX + dX, GraphDrawY + dY);

		Percent = value * 100 / totalData;

	
		WCHAR szNum[30];
		wsprintf(szNum, L"%d%%", Percent);
		

		double theta = AccRadian - (radian / 2);
		int Px = midX + diameter / 4 * cos(theta);
		int Py = midY + diameter / 4 * sin(theta);

		SetTextColor(m_hMemDc, BLACK);
		TextOut(m_hMemDc, Px + 1, Py, szNum, lstrlenW(szNum));
		TextOut(m_hMemDc, Px, Py + 1, szNum, lstrlenW(szNum));
		TextOut(m_hMemDc, Px - 1, Py, szNum, lstrlenW(szNum));
		TextOut(m_hMemDc, Px, Py - 1, szNum, lstrlenW(szNum));


		SetTextColor(m_hMemDc, WHITE);
		TextOut(m_hMemDc, Px, Py, szNum, lstrlenW(szNum));
		dX = iX;
		dY = iY;
	}


	int height = columnRect.bottom - columnRect.top;
	int length = columnRect.right - columnRect.left;
	int yGap = 7;
	int xCnt = length / 4;
	int yCnt = (height / 15) + yGap;
	int PosX = columnRect.left + xCnt;
	int	PosY = columnRect.top + yCnt;
	SelectObject(m_hMemDc, m_girdFont);
	for (int i = 0; i < ServerID; i++)
	{
		SelectObject(m_hMemDc, m_graphLine[i]);
		SelectObject(m_hMemDc, m_graphBarColor[i]);
		Rectangle(m_hMemDc, PosX, PosY, PosX + xCnt, PosY - yGap);

		SelectObject(m_hMemDc, m_titlePEN);
		SetTextAlign(m_hMemDc, TA_TOP | TA_LEFT);
		TextOut(m_hMemDc, PosX + (xCnt) + 1, PosY - (yGap)-3, m_info[i].szName, lstrlenW(m_info[i].szName));

		PosY += yGap + 10;
	}


	SetTextAlign(m_hMemDc, TA_TOP | TA_LEFT);

}

void CGraphUnit::FilpDC(HDC hdc)
{
	BitBlt(hdc, 0, 0, m_ClientRect.right, m_ClientRect.bottom, m_hMemDc, 0, 0, SRCCOPY);
}


void CGraphUnit::SetInformation(WCHAR *WindowName, WCHAR *UnitName,  COLORREF TitleBackColor, COLORREF GraphBackColor, int AlertValue, int MaxValue)
{
	m_alertValue = AlertValue;
	m_maxValue = MaxValue;
	lstrcpyW(m_titleName, WindowName);

	m_titleBackColor = CreateSolidBrush(TitleBackColor);
	m_graphBackColor = CreateSolidBrush(GraphBackColor);

	if (UnitName != nullptr)
		lstrcpyW(m_Unit, UnitName);
	
}
void CGraphUnit::AddColumn(WCHAR *ColumnName, COLORREF GraphColor,  int dataType)
{
	stColumnInfo *p = &(m_info[ServerID]);

	lstrcpyW(p->szName, ColumnName);
	p->u64ServerID = ServerID;

	m_graphBarColor[ServerID] = CreateSolidBrush(GraphColor);
	m_graphLine[ServerID] = CreatePen(PS_SOLID, 1, GraphColor);
	
	p->iType = dataType;
	ServerID++;
}

// ===========================================================
// 큐에 데이터를 넣는다. 
// ===========================================================
bool CGraphUnit::InsertData(ULONG64 ServerID, int DataType, int Value)
{
	if (m_info[ServerID].queue.freeSize() <= 0)
		m_info[ServerID].queue.Dequeue(nullptr);
	
	int value = (min(Value, m_maxValue));
	value = max(1, value);

	m_info[ServerID].queue.Enqueue(value);
	// 위험요소인가?
	if (m_alertValue <= Value)
	{
		m_alert = true;
		SetTimer(m_hWnd, 0, 1000, NULL);
		SendMessage(m_hWndParent, UM_ALERT, 0, 0);
	}

	InvalidateRect(m_hWnd, NULL, false);

	return true;
}