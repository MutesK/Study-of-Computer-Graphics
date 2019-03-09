#include "stdafx.h"
#include "Matrix3D.h"


namespace MathUtil
{

	Matrix3D Matrix3D::zero = Matrix3D(0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f);

	Matrix3D Matrix3D::identity = Matrix3D(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);

	Matrix3D::Matrix3D(float e11, float e12, float e13,
		float e21, float e22, float e23,
		float e31, float e32, float e33)
		: _e11(e11), _e12(e12), _e13(e13),
		  _e21(e21), _e22(e22), _e23(e23),
		  _e31(e31), _e32(e32), _e33(e33)
	{
	}

	Matrix3D::~Matrix3D()
	{
	}

	void Matrix3D::Set(float e11, float e12, float e13,
		float e21, float e22, float e23,
		float e31, float e32, float e33)
	{
		_e11 = e11;
		_e12 = e12;
		_e13 = e13;

		_e21 = e21;
		_e22 = e22;
		_e23 = e23;

		_e31 = e31;
		_e32 = e32;
		_e33 = e33;
	}

	void Matrix3D::SetIdentity()
	{
		_e11 = 1.0f;
		_e12 = 0.0f;
		_e13 = 0.0f;

		_e21 = 0.0f;
		_e22 = 1.0f;
		_e23 = 0.0f;

		_e31 = 0.0f;
		_e32 = 0.0f;
		_e33 = 1.0f;
	}

	void Matrix3D::SetRotation(float theta)
	{
		SetIdentity();
		_e11 = cosf(theta); _e12 = -sinf(theta);
		_e21 = sinf(theta); _e22 = cosf(theta);
	}

	void Matrix3D::SetShear(float shearXParalleToY, float shearYParalleToX)
	{
		SetIdentity();

		_e11 = 1.0f; _e12 = shearYParalleToX;
		_e21 = shearXParalleToY; _e22 = 1.0f;
	}

	void Matrix3D::SetScale(float uniScale)  // Affine Transform ¾ÆÇÉº¯È¯
	{
		SetIdentity();

		_e11 = uniScale;
		_e22 = uniScale;
		_e33 = uniScale;
	}

	void Matrix3D::SetTranslation(float tx, float ty)
	{
		SetIdentity();
		_e13 = tx;
		_e23 = ty;
	}

	bool Matrix3D::GetBasis(Vector2D& basis, int basisIndex)
	{
		if (basisIndex == 0) {
			basis.set_x(_e11);
			basis.set_y(_e21);
		}
		else if (basisIndex == 1)
		{
			basis.set_x(_e11);
			basis.set_y(_e22);
		}
		else
		{
			return false;
		}

		return true;
	}

	MathUtil::Matrix3D Matrix3D::InverseMatrix() const
	{
		auto GetMinor = [](float a, float b, float c, float d)
		{
			return a * d - b * c;
		};
		const float det = GetDeterminant();
		Matrix3D adj;
		// Get minor and apply cofactor
		const float m11 = +GetMinor(_e22, _e23, _e32, _e33);
		const float m12 = -GetMinor(_e21, _e23, _e31, _e33);
		const float m13 = +GetMinor(_e21, _e22, _e31, _e32);
		const float m21 = -GetMinor(_e12, _e13, _e32, _e33);
		const float m22 = +GetMinor(_e11, _e13, _e31, _e33);
		const float m23 = -GetMinor(_e11, _e12, _e31, _e32);
		const float m31 = +GetMinor(_e12, _e13, _e22, _e23);
		const float m32 = -GetMinor(_e11, _e13, _e21, _e23);
		const float m33 = +GetMinor(_e11, _e12, _e21, _e22);
		// set Adjugate matrix
		adj.Set(
			m11, m21, m31,
			m12, m22, m32,
			m13, m23, m33);
		return (1.0f / det) * adj;

	}

	float Matrix3D::GetDeterminant() const
	{
		const float& a = _e11;
		const float& b = _e12;
		const float& c = _e13;
		const float& d = _e21;
		const float& e = _e22;
		const float& f = _e23;
		const float& g = _e31;
		const float& h = _e32;
		const float& i = _e33;
		return a * e*i - a * f*h - b * d*i + b * f*g + c * d*h - c * e*g;
	}

}