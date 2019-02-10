#pragma once

#include "stdafx.h"

namespace MathUtil
{
	class Vector2D
	{
	public:
		Vector2D(float xpos ,float ypos);
		Vector2D(int xpos, int ypos);
		~Vector2D();

		Vector2D operator+(const Vector2D& hs);
		Vector2D operator-(const Vector2D& hs);
		Vector2D operator*(const Vector2D& hs);
		Vector2D operator*(float scalar);

		GET_CONST_ATTRIBUTE(float, x);
		GET_CONST_ATTRIBUTE(float, y);

	private:
		float _x;
		float _y;
	};
}

