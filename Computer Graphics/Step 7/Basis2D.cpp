#include "stdafx.h"
#include "Basis2D.h"
#include "Vector.h"

namespace MathUtil
{
	Basis2D::Basis2D()
	{
		_basis_i = Vector2D(1, 0);
		_basis_j = Vector2D(0, 1);
	}


	Basis2D::~Basis2D()
	{
	}

	void Basis2D::SetInfo(const Vector2D& basis1, const Vector2D& basis2)
	{
		_basis_i = basis1;
		_basis_j = basis2;
	}
	
	Vector2D Basis2D::Transform(const Vector2D& input)
	{
		Vector2D t0 = _basis_i * input.get_x();
		Vector2D t1 = _basis_j * input.get_y();

		Vector2D temp(t0.get_x() + t1.get_x(), t0.get_y() + t1.get_y());
		return temp;
	}
}
