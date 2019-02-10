#pragma once

#include "stdafx.h"
#include "Vector.h"
#include "ScreenCoordinate.h"
#include "Basis2D.h"

namespace MathUtil
{
	extern ScreenCoordinate    g_screenCoordinate;
	extern Basis2D  g_basis2;

	void DrawLine(HDC hdc, const Vector2D& rVec, const Vector2D& lVec, int linewidth, 
		int penStyle, COLORREF color);

	void DrawAxis(HDC hdc, int numHorizontalGrid, int numVerticalGrid, COLORREF color = RGB(64, 64, 64));
	void DrawGrid(HDC hdc, int numHorizontalGrid, int numVerticalGrid, COLORREF color = RGB(64, 64, 64));
	void SetScreenCoordinate(const ScreenCoordinate& screenCoord);
	void SetBasis2(const Basis2D& basis2);
}