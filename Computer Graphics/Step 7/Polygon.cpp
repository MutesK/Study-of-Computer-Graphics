#include "stdafx.h"
#include "Polygon.h"
#include "MathUtil.h"

namespace MathUtil
{
	// 표면을 고려하지 않고, 삼각형을 구성하는 선만 고려한다.
	// 버텍스의 갯수와 선의 갯수는 정형적인 비례관계가 없으므로, 효과적으로 추력
	void DrawIndexPrimitive(HDC hdc, std::array<int, 100>&  _indexbuffer,
		int primitiveCounter, std::array<Vector3D, 100>& _vertexbuffer, COLORREF color)
	{
		int i1, i2;
		int counter = 0;

		for (int i = 0; i < primitiveCounter; ++i)
		{
			i1 = _indexbuffer[counter];
			i2 = _indexbuffer[counter + 1];

			// Draw
			DrawLine(hdc, _vertexbuffer[i1]._x, _vertexbuffer[i1]._y ,
				_vertexbuffer[i2]._x, _vertexbuffer[i2]._y, 2, PS_SOLID, color);

			counter += 2;
		}
	}

	Polygon::Polygon()
	{
		_sizeIndex = 0;
		_sizeVertex = 0;
		_color = RGB(0, 0, 255);
	}


	Polygon::~Polygon()
	{
	}

	void Polygon::SetIndexBuffer()  // 인덱스의 순서는 시계방향 -> 면의 방향을 결정해준다.
	{
		int buffer[] = { 0, 1, // Vertex Index
						1, 3,
						3, 0,
						1, 2,
						2, 3,
						3, 1 };

		for (int i = 0; i < 12; ++i)
			_indexbuffer[i] = buffer[i];

		_sizeIndex = 12;
	}

	void Polygon::SetVertexBuffer()
	{
		_vertexbuffer[0] = (Vector3D{ -5.0f, -5.0f, 0.0f });
		_vertexbuffer[1] = (Vector3D{ -5.0f, 5.0f, 0.0f });
		_vertexbuffer[2] = (Vector3D{ 5.0f, 5.0f, 0.0f });
		_vertexbuffer[3] = (Vector3D{ 5.0f, -5.0f, 0.0f });

		_sizeVertex = 4;
	}

	void Polygon::Render(HDC hdc)
	{
		DrawIndexPrimitive(hdc, _indexbuffer, 6, _vertexbuffer, _color);
	}

}