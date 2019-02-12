#pragma once

#include "Vector.h"

namespace MathUtil
{
	class ScreenCoordinate
	{
	public:
		ScreenCoordinate();
		~ScreenCoordinate();

		void SetInfo(const Vector2D& axis0,
			const Vector2D& axis1, const Vector2D& origin);
		Vector2D Transform(const Vector2D& input);

		GET_SET_ATTRIBUTE(Vector2D, origin);
	private:
		Vector2D _Xaxis;
		Vector2D _Yaxis;
		Vector2D _origin;

	};
}

