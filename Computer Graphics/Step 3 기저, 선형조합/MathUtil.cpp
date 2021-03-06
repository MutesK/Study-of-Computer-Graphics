#include "stdafx.h"
#include "MathUtil.h"

namespace MathUtil
{
	ScreenCoordinate    g_screenCoordinate;
	Basis2D  g_basis2;

	void SetScreenCoordinate(const ScreenCoordinate& screenCoord)
	{
		g_screenCoordinate = screenCoord;
	}

	void SetBasis2(const Basis2D& basis2)
	{
		g_basis2 = basis2;
	}

	void DrawLine(HDC hdc, const Vector2D& rVec, const Vector2D& lVec, int linewidth,
		int penStyle, COLORREF color)
	{
		Vector2D v0 = g_basis2.Transform(rVec);
		Vector2D v1 = g_basis2.Transform(lVec);

		// ��ǥ�迡 �°� ��ǥ ��ȯ
		v0 = g_screenCoordinate.Transform(v0);
		v1 = g_screenCoordinate.Transform(v1);

		HPEN hpen = CreatePen(penStyle, linewidth, color);
		HGDIOBJ original = SelectObject(hdc, hpen); // �� ��ü

		{
			MoveToEx(hdc, (int)v0.get_x(), (int)v0.get_y(), nullptr);
			LineTo(hdc, (int)v1.get_x(), (int)v1.get_y());
		}

		SelectObject(hdc, original);
		DeleteObject(hpen);
	}

	void DrawAxis(HDC hdc, int numHorizontalGrid, int numVerticalGrid, COLORREF color)
	{
		// Y Axis
		{
			Vector2D v0 = Vector2D(0, -numVerticalGrid / 2);
			Vector2D v1 = Vector2D(0, numVerticalGrid / 2);
			DrawLine(hdc, v0, v1, 2, PS_SOLID, color);
		}

		// X Axis
		{
			Vector2D v0 = Vector2D(-numHorizontalGrid / 2, 0);
			Vector2D v1 = Vector2D(numHorizontalGrid / 2, 0);
			DrawLine(hdc, v0, v1, 2, PS_SOLID, color);
		}
	}

	void DrawGrid(HDC hdc, int numHorizontalGrid, int numVerticalGrid, COLORREF color)
	{
		int hbegin = (int)(-numHorizontalGrid / 2.0f - 0.5f);

		for (int count = 0; count <= numHorizontalGrid; ++count)
		{
			Vector2D v0 = Vector2D(hbegin, 0) + Vector2D(0, -numVerticalGrid / 2);
			Vector2D v1 = Vector2D(hbegin, 0) + Vector2D(0, numVerticalGrid / 2);

			DrawLine(hdc, v0, v1, 1, PS_DOT, color);
			hbegin++;
		}

		int vbegin = (int)(-numVerticalGrid / 2.0f - 0.5f);
		for (int count = 0; count <= numVerticalGrid; ++count)
		{
			Vector2D v0 = Vector2D(0, vbegin) + Vector2D(-numHorizontalGrid / 2, 0);
			Vector2D v1 = Vector2D(0, vbegin) + Vector2D(numHorizontalGrid / 2, 0);

			DrawLine(hdc, v0, v1, 1, PS_DOT, color);
			vbegin++;
		}
	}
}