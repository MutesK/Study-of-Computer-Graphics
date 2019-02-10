#include "stdafx.h"
#include "Vector.h"

namespace MathUtil
{
	Vector2D::Vector2D()
		:_x(0), _y(0)
	{
	}
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

}
