#pragma once

#include "stdafx.h"

namespace MathUtil
{
	class Vector2D
	{
	public:
		static Vector2D zero; // øµ∫§≈Õ
		static Vector2D one; 
		static Vector2D x_unit;  // ¥‹¿ß∫§≈Õ
		static Vector2D y_unit;

		// Linear Interpolation
		static Vector2D LinearInterpolate(const Vector2D& begin, const Vector2D& end,
			float ratio);

	public:
		Vector2D();
		Vector2D(float xpos, float ypos);
		Vector2D(int xpos, int ypos);
		~Vector2D();

		float Length() const
		{
			return sqrtf(_x*_x + _y * _y);
		}

		void Normalize()
		{
			const float length = Length();
			_x = _x / length;
			_y = _y / length;
		}

		GET_SET_ATTRIBUTE(float, x);
		GET_CONST_ATTRIBUTE(float, x);
		GET_SET_ATTRIBUTE(float, y);
		GET_CONST_ATTRIBUTE(float, y);

		friend Vector2D operator*(const Vector2D& hs, float scalar);
		friend Vector2D operator*(const Vector2D& rhs, const Vector2D& lhs);
		friend Vector2D operator+(const Vector2D& rhs, const Vector2D& lhs);
		friend Vector2D operator-(const Vector2D& rhs, const Vector2D& lhs);
	private:
		float _x;
		float _y;
	};

	inline Vector2D operator*(const Vector2D& hs, float scalar)
	{
		Vector2D temp(hs.get_x() * scalar, hs.get_y() * scalar);
		return temp;
	}

	inline Vector2D operator*(const Vector2D& rhs, const Vector2D& lhs)
	{
		Vector2D temp(rhs.get_x() * lhs.get_x(), rhs.get_y() * lhs.get_y());
		return temp;
	}

	inline Vector2D operator+(const Vector2D& rhs, const Vector2D& lhs)
	{
		Vector2D temp(rhs.get_x() + lhs.get_x(), rhs.get_y() + lhs.get_y());
		return temp;
	}

	inline Vector2D operator-(const Vector2D& rhs, const Vector2D& lhs)
	{
		Vector2D temp(rhs.get_x() - lhs.get_x(), rhs.get_y() - lhs.get_y());
		return temp;
	}

}

