#pragma once

namespace MathUtil
{
	class Vector3D
	{
	public:
		Vector3D()
		{}
		Vector3D(float tx, float ty, float tz)
		{
			_x = tx;
			_y = ty;
			_z = tz;
		}
		Vector3D(int tx, int ty, int tz)
		{
			_x = tx;
			_y = ty;
			_z = tz;
		}
		~Vector3D()
		{}

		float _x = 0.0f, _y = 0.0f, _z = 0.0f;
	};

}