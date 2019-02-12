#include "stdafx.h"
#include "Vector.h"

namespace MathUtil
{
	Vector2D Vector2D::zero = Vector2D(0, 0);
	Vector2D Vector2D::one = Vector2D(1, 1);
	Vector2D Vector2D::x_unit = Vector2D(1, 0);
	Vector2D Vector2D::y_unit = Vector2D(0, 1);

	Vector2D Vector2D::LinearInterpolate(const Vector2D& begin, const Vector2D& end,
		float ratio)
	{
		float ratio_temp = __min(1, __max(0, ratio));

		Vector2D temp;
		temp.set_x(begin.get_x() + (end.get_x() - begin.get_x()) * ratio_temp);
		temp.set_y(begin.get_y() + (end.get_y() - begin.get_y()) * ratio_temp);

		return temp;
	}


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
