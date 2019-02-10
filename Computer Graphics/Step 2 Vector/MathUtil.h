#pragma once

#include "stdafx.h"
#include "Vector.h"

namespace MathUtil
{
	class Vector2D;

	void DrawLine(HDC& hdc, const Vector2D& rVec, const Vector2D& lVec);
}