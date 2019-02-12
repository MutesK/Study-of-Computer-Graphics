#pragma once

#include "Vector.h"

namespace MathUtil
{
	class Matrix2D
	{
	public:
		static Matrix2D zero; // 영행렬
		static Matrix2D identity; // 단위 행렬
	public:
		Matrix2D(float e11 = 1.0f, float e12 = 0.0f, float e21 = 0.0f, float e22 = 1.0f)
			:_e11(e11), _e12(e12), _e21(e21), _e22(e22)
		{}
		~Matrix2D()
		{}

		void Set(float e11, float e12, float e21, float e22)
		{
			_e11 = e11;
			_e12 = e12;
			_e21 = e21;
			_e22 = e22;
		}

		// 단위 행렬화
		void SetIdentity()
		{
			_e11 = 1.0f, _e12 = 0.0f;
			_e21 = 0.0f, _e22 = 1.0f;
		}

		// 회전 행렬화
		void SetRotation(float theta)
		{
			_e11 = cosf(theta), _e12 = -sinf(theta);
			_e21 = sinf(theta), _e22 = cosf(theta);
		}

		// 쉐어 변환행렬화
		void SetShear(float shearXParallelToY, float shearYParallelToX)
		{
			_e11 = 1.0f, _e12 = shearYParallelToX;
			_e21 = shearXParallelToY, _e22 = 1.0f;
		}

		bool GetBasis(Vector2D& basis, int basisIndex)
		{
			switch (basisIndex)
			{
			case 0:
				basis.set_x(_e11);
				basis.set_y(_e21);
				break;
			case 1:
				basis.set_x(_e12);
				basis.set_y(_e22);
				break;
			default:
				return false;
			}

			return true;
		}

		GET_SET_ATTRIBUTE(float, e11);
		GET_SET_ATTRIBUTE(float, e12);
		GET_SET_ATTRIBUTE(float, e21);
		GET_SET_ATTRIBUTE(float, e22);
		GET_CONST_ATTRIBUTE(float, e11);
		GET_CONST_ATTRIBUTE(float, e12);
		GET_CONST_ATTRIBUTE(float, e21);
		GET_CONST_ATTRIBUTE(float, e22);

		friend Matrix2D operator*(const Matrix2D& a, const Matrix2D& b);

	private:
		float _e11, _e12;
		float _e21, _e22;
	};

	inline Vector2D operator*(const Matrix2D& m, const Vector2D& v)
	{
		Vector2D temp;
		temp.set_x(m.get_e11() * v.get_x() + m.get_e12() * v.get_y());
		temp.set_y(m.get_e21() * v.get_x() + m.get_e22() * v.get_y());

		return temp;
	}

	inline Matrix2D operator*(float scalar, const Matrix2D& m)
	{
		Matrix2D temp;

		temp.set_e11(scalar * temp.get_e11());
		temp.set_e12(scalar * temp.get_e12());
		temp.set_e21(scalar * temp.get_e21());
		temp.set_e22(scalar * temp.get_e22());

		return temp;
	}

	inline Matrix2D operator*(const Matrix2D& a, const Matrix2D& b)
	{
		Matrix2D temp;

		temp.set_e11(a.get_e11() * b.get_e11() + a.get_e12() * b.get_e21());
		temp.set_e12(a.get_e11() * b.get_e12() + a.get_e12() * b.get_e22());

		temp.set_e21(a.get_e21() * b.get_e11() + a.get_e22() * b.get_e21());
		temp.set_e22(a.get_e21() * b.get_e12() + a.get_e22() * b.get_e22());

		return temp;


	}

}