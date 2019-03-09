#include "stdafx.h"
#include "ScreenCoordinate.h"

namespace MathUtil
{
	ScreenCoordinate::ScreenCoordinate()
	{
		_Xaxis = Vector2D(1, 0);
		_Yaxis = Vector2D(0, -1);
		_origin = Vector2D(0, 0);
	}


	ScreenCoordinate::~ScreenCoordinate()
	{
	}

	void ScreenCoordinate::SetInfo(const Vector2D& axis0,
		const Vector2D& axis1, const Vector2D& origin)
	{
		_Xaxis = axis0;
		_Yaxis = axis1;
		_origin = origin;
	}

	Vector2D ScreenCoordinate::Transform(const Vector2D& input)
	{
		Vector2D t0 = _Xaxis * input.get_x();
		Vector2D t1 = _Yaxis * input.get_y();
		Vector2D temp(t0.get_x() + t1.get_x() + _origin.get_x(),
			t0.get_y() + t1.get_y() + _origin.get_y());

		return temp;
	}
}