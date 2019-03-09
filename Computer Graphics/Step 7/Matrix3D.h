#pragma once

#include "Vector.h"

namespace MathUtil
{

	class Matrix3D
	{
	public:
		static Matrix3D zero;
		static Matrix3D identity;

		Matrix3D(float e11 = 1.0f, float e12 = 0.0f, float e13 = 0.0f,
			float e21 = 0.0f, float e22 = 1.0f, float e23 = 0.0f,
			float e31 = 0.0f, float e32 = 0.0f, float e33 = 1.0f);
		~Matrix3D();

		void Set(float e11, float e12, float e13,
			float e21, float e22, float e23,
			float e31, float e32, float e33);
		void SetIdentity();

		void SetRotation(float theta);

		void SetShear(float shearXParalleToY, float shearYParalleToX);

		void SetScale(float uniScale);

		void SetTranslation(float tx, float ty);

		bool GetBasis(Vector2D& basis, int basisIndex);

		Matrix3D InverseMatrix() const;
		float	 GetDeterminant() const;

		GET_SET_ATTRIBUTE(float, e11);
		GET_SET_ATTRIBUTE(float, e12);
		GET_SET_ATTRIBUTE(float, e13);
		GET_SET_ATTRIBUTE(float, e21);
		GET_SET_ATTRIBUTE(float, e22);
		GET_SET_ATTRIBUTE(float, e23);
		GET_SET_ATTRIBUTE(float, e31);
		GET_SET_ATTRIBUTE(float, e32);
		GET_SET_ATTRIBUTE(float, e33);

		GET_CONST_ATTRIBUTE(float, e11);
		GET_CONST_ATTRIBUTE(float, e12);
		GET_CONST_ATTRIBUTE(float, e13);
		GET_CONST_ATTRIBUTE(float, e21);
		GET_CONST_ATTRIBUTE(float, e22);
		GET_CONST_ATTRIBUTE(float, e23);
		GET_CONST_ATTRIBUTE(float, e31);
		GET_CONST_ATTRIBUTE(float, e32);
		GET_CONST_ATTRIBUTE(float, e33);

		friend inline Vector2D operator*(const Vector2D& v, const Matrix3D& m);
		friend inline Vector2D operator*(const Matrix3D& v, const Vector2D& m);
		friend inline Matrix3D operator*(float scalar, const Matrix3D& m);
		friend inline Matrix3D operator*(const Matrix3D& m0, const Matrix3D& m1);

	private:
		float _e11, _e12, _e13;
		float _e21, _e22, _e23;
		float _e31, _e32, _e33;
	};

	inline Vector2D operator*(const Vector2D& v, const Matrix3D& m)
	{
		Vector2D temp;

		temp.set_x(m._e11 * v.get_x() + m._e21 * v.get_y() + m._e31 * 1.0f);
		temp.set_y(m._e12 * v.get_x() + m._e22 * v.get_y() + m._e32 * 1.0f);

		const float z = v.get_x() * m._e13 + v.get_y() * m._e23 + 1.0f * m._e33;

		temp.set_x(temp.get_x() / z);
		temp.set_y(temp.get_y() / z);

		return temp;
	}

	inline Vector2D operator*(const Matrix3D& m, const Vector2D& v)
	{
		Vector2D temp;

		temp.set_x(m._e11 * v.get_x() + m._e12 * v.get_y() + m._e13 * 1.0f);
		temp.set_y(m._e21 * v.get_x() + m._e22 * v.get_y() + m._e23 * 1.0f);

		const float z = v.get_x() * m._e31 + v.get_y() * m._e32 + 1.0f * m._e33;

		temp.set_x(temp.get_x() / z);
		temp.set_y(temp.get_y() / z);

		return temp;
	}

	inline Matrix3D operator*(float scalar, const Matrix3D& m)
	{
		Matrix3D temp;
		temp._e11 = scalar * m._e11;
		temp._e12 = scalar * m._e12;
		temp._e13 = scalar * m._e13;

		temp._e21 = scalar * m._e21;
		temp._e22 = scalar * m._e22;
		temp._e23 = scalar * m._e23;

		temp._e31 = scalar * m._e31;
		temp._e32 = scalar * m._e32;
		temp._e33 = scalar * m._e33;

		return temp;
	}

	// Çà·Ä °ö¼À
	inline Matrix3D operator*(const Matrix3D& m0, const Matrix3D& m1)
	{
		Matrix3D temp;

		temp._e11 = m0._e11 * m1._e11 + m0._e12 * m1._e21 + m0._e13 * m1._e31;
		temp._e12 = m0._e11 * m1._e12 + m0._e12 * m1._e22 + m0._e13 * m1._e32;
		temp._e13 = m0._e11 * m1._e13 + m0._e12 * m1._e23 + m0._e13 * m1._e33;

		temp._e21 = m0._e21 * m1._e11 + m0._e22 * m1._e21 + m0._e23 * m1._e31;
		temp._e22 = m0._e21 * m1._e12 + m0._e22 * m1._e22 + m0._e23 * m1._e32;
		temp._e23 = m0._e21 * m1._e13 + m0._e22 * m1._e23 + m0._e23 * m1._e33;

		temp._e31 = m0._e31 * m1._e11 + m0._e32 * m1._e21 + m0._e33 * m1._e31;
		temp._e32 = m0._e31 * m1._e12 + m0._e32 * m1._e22 + m0._e33 * m1._e32;
		temp._e33 = m0._e31 * m1._e13 + m0._e32 * m1._e23 + m0._e33 * m1._e33;

		return temp;
	}
}