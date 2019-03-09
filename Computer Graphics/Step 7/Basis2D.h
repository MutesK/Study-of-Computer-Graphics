#pragma once

#include "Vector.h"

namespace MathUtil
{
	class Basis2D
	{
	public:
		Basis2D();
		~Basis2D();

		void SetInfo(const Vector2D& basis1, const Vector2D& basis2);
		// 선형 변환
		Vector2D Transform(const Vector2D& input);

	private:
		Vector2D _basis_i;
		Vector2D _basis_j;
	};
}

