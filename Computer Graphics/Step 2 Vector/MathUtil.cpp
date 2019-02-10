#include "stdafx.h"
#include "MathUtil.h"

namespace MathUtil
{
	void DrawLine(HDC& hdc, const Vector2D& rVec, const Vector2D& lVec)
	{
		MoveToEx(hdc, (int)rVec.get_x(), (int)rVec.get_y(), nullptr);
		LineTo(hdc, (int)lVec.get_x(), (int)lVec.get_y());
	}
}