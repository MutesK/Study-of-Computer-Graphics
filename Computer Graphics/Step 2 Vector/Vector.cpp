#include "stdafx.h"
#include "Vector.h"

namespace MathUtil
{
	Vector2D::Vector2D(float xpos, float ypos)
		:_x(xpos), _y(ypos)
	{
	}

	Vector2D::Vector2D(int xpos, int ypos)
		:_x(xpos), _y(ypos)
	{
	}

	Vector2D::~Vector2D()
	{
	}

	Vector2D Vector2D::operator+(const Vector2D& hs)
	{
		Vector2D obj(_x + hs._x, _y + hs._y);
		return obj;
	}
	Vector2D Vector2D::operator-(const Vector2D& hs)
	{
		Vector2D obj(_x - hs._x, _y - hs._y);
		return obj;
	}
	Vector2D Vector2D::operator*(const Vector2D& hs)
	{
		Vector2D obj(_x * hs._x, _y * hs._y);
		return obj;
	}
	Vector2D Vector2D::operator*(float scalar)
	{
		Vector2D obj(_x * scalar, _y * scalar);
		return obj;
	}
}
