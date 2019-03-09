#pragma once

#include <array>
#include "Vector3D.h"

namespace MathUtil
{
	class Polygon
	{
	public:
		Polygon();
		~Polygon();

		void SetIndexBuffer();
		void SetVertexBuffer();
		void Render(HDC hdc);
		void SetColor(COLORREF color)
		{
			_color = color;
		}
	private:
		std::array<int, 100> _indexbuffer;
		int	_sizeIndex;
		std::array<Vector3D, 100> _vertexbuffer;
		int _sizeVertex;

		COLORREF _color;
	};
}