#pragma once

#include "stdafx.h"

class CGraphUnit
{
public:
	enum TYPE
	{
		BAR_SINGLE_VERT,
		BAR_SINGLE_HORZ,
		BAR_COLUMN_VERT,
		BAR_COLUMN_HORZ,
		LINE_SINGLE,
		LINE_MULTI,
		PIE
	};
	typedef struct ST_COLUMN_INFO
	{
		ULONG64 u64ServerID;
		int iType;		// 데이터 구분을 위해서
		WCHAR szName[WINDOW_NAME];
		CQueue<int> queue;
	} stColumnInfo;


protected:
	HBITMAP m_hMemBitMap;
	HBITMAP m_hOldMemBitMap;
	RECT m_ClientRect;
	HDC m_hMemDc;
	TYPE m_type;

	stColumnInfo m_info[COLUMN_MAX];
	ULONG64 ServerID ;

	// ===========================================================
	// 위험 요소 관리
	// ===========================================================
	bool m_alert;
	int m_alertValue;
	int m_maxValue;

	HWND m_hWnd;
	HWND m_hWndParent;		

	// ===========================================================
	// 원본데이터 관리
	// ===========================================================
	WCHAR m_titleName[30];
	WCHAR m_className[100];

	// ===========================================================
	// TITLE에 관련된 변수
	// ===========================================================
	WCHAR m_Unit[45];
	RECT m_titleRect;
	HBRUSH m_titleBackColor;
	HPEN m_titlePEN;
	HFONT m_titleFont;

	// ===========================================================
	// 그래프에 관련된 변수
	// ===========================================================
	RECT m_graphRect;
	HBRUSH m_graphBackColor;

	HPEN m_graphLine[COLUMN_MAX];  // 선 색깔
	HBRUSH m_graphBarColor[COLUMN_MAX];

	HPEN m_gridPen;				  // 그리드 색깔
	HFONT m_girdFont;			  // 그리드 폰트(크기)
	HBRUSH m_clientRectColor;


protected:
	void FilpDC(HDC hdc);

	int reSetPosY(int max, int clientHeight, int posY)
	{
		// f(max) = clientHeight 
		// max : clientHeight = posY : 찍혀야될 위치(ret)
		// max * ret = posY * clientHeight;
		// ret = (posY * clientHeight ) / max
		// f(0) = 0;
		if (posY == 0)
			return 0;

		return ((posY * clientHeight) / max) ;
	}
	void Draw_TITLE();
	void Single_DrawSetting(int _ColumnWidth, int _ColumnHeight = 0);

	void Draw_LINESINGLE();
	void Draw_LINEMULTI();
	void Draw_BARSINGLEHORZ();
	void Draw_BARCOLUMNHORZ();
	void Draw_PIE();
	void ComponentSetting();

public:
	// 윈도우 클래스 구조체와 핸들러 자동생성하는 생성자
	CGraphUnit(HINSTANCE hInstance, HWND hWndParent, TYPE type,
		int posX, int posY, int width, int height);
	~CGraphUnit();

	static LRESULT CALLBACK  WndProc(HWND, UINT, WPARAM, LPARAM);

	bool InsertData(ULONG64 ServerID, int DataType, int Value);

	// ===================================================================
	// 타이틀 윈도우 이름과 타이틀 그림, 그래프영역 그림 설정
	// ===================================================================
	void SetInformation(WCHAR *WindowName, WCHAR *UnitName, COLORREF TitleBackColor, COLORREF GraphBackColor, int alert, int Max);
	void AddColumn(WCHAR *ColumnName, COLORREF GraphColor, int dataType);
};

