#pragma once

#include "stdafx.h"

namespace MathUtil
{
	class Vector2D
	{
	public:
		Vector2D();
		Vector2D(float xpos, float ypos);
		Vector2D(int xpos, int ypos);
		~Vector2D();

		GET_SET_ATTRIBUTE(float, x);
		GET_CONST_ATTRIBUTE(float, x);
		GET_SET_ATTRIBUTE(float, y);
		GET_CONST_ATTRIBUTE(float, y);

		friend Vector2D operator*(const Vector2D& hs, float scalar);
		friend Vector2D operator*(const Vector2D& rhs, const Vector2D& lhs);
		friend Vector2D operator+(const Vector2D& rhs, const Vector2D& lhs);
		friend Vector2D operator-(const Vector2D& rhs, const Vector2D& lhs);
	private:
		float _x;
		float _y;
	};

	inline Vector2D operator*(const Vector2D& hs, float scalar)
	{
		Vector2D temp(hs.get_x() * scalar, hs.get_y() * scalar);
		return temp;
	}

	inline Vector2D operator*(const Vector2D& rhs, const Vector2D& lhs)
	{
		Vector2D temp(rhs.get_x() * lhs.get_x(), rhs.get_y() * lhs.get_y());
		return temp;
	}

	inline Vector2D operator+(const Vector2D& rhs, const Vector2D& lhs)
	{
		Vector2D temp(rhs.get_x() + lhs.get_x(), rhs.get_y() + lhs.get_y());
		return temp;
	}

	inline Vector2D operator-(const Vector2D& rhs, const Vector2D& lhs)
	{
		Vector2D temp(rhs.get_x() - lhs.get_x(), rhs.get_y() - lhs.get_y());
		return temp;
	}

}

