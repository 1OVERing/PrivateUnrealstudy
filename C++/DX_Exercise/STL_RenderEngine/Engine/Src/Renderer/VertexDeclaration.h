#pragma once

#ifndef _Vertex_Declaration_
#define _Vertex_Declaration_

#include "Core.h"

#include "Math/Vector2f.h"
#include "Math/Vector3f.h"

namespace Ronnie
{
	struct ENGINE_API VertexPosition
	{
		float x, y, z;

		VertexPosition()
			: x(0.0f), y(0.0f), z(0.0f)
		{
		}

		VertexPosition(float x, float y, float z)
			: x(x), y(y), z(z)
		{
		}
	};

	struct ENGINE_API VertexPositionColor
	{
		float x, y, z;
		float r, g, b;

		VertexPositionColor()
			: x(0.0f), y(0.0f), z(0.0f),
			r(0.0f), g(0.0f), b(0.0f)
		{
		}

		VertexPositionColor(
			float x, float y, float z, 
			float r, float g, float b)
			: x(x), y(y), z(z),
			r(r), g(g), b(b)
		{
		}
	};

	struct ENGINE_API VertexPositionColorUV
	{
		float x, y, z;
		float r, g, b;
		float u, v;

		VertexPositionColorUV()
			: x(0.0f), y(0.0f), z(0.0f),
			r(0.0f), g(0.0f), b(0.0f),
			u(0.0f), v(0.0f)
		{
		}

		VertexPositionColorUV(
			float x, float y, float z,
			float r, float g, float b,
			float u, float v)
			: x(x), y(y), z(z),
			r(r), g(g), b(b),
			u(u), v(v)
		{
		}

		VertexPositionColorUV(
			Vector3f position,
			Vector3f color,
			Vector2f uv)
			: x(position.x), y(position.y), z(position.z),
			r(color.x), g(color.y), b(color.z),
			u(uv.x), v(uv.y)
		{
		}
	};

	struct ENGINE_API VertexPositionUVNormal
	{
		Vector3f position;
		Vector2f texCoord;
		Vector3f normal;

		VertexPositionUVNormal()
			: position(), texCoord(), normal()
		{}
		
		VertexPositionUVNormal(
			const Vector3f& position,
			const Vector2f& texCoord,
			const Vector3f& normal)
			: position(position), 
			texCoord(texCoord), 
			normal(normal)
		{}
	};

	struct ENGINE_API VertexPositionUVNormalBinormalTangent
	{
		Vector3f position;
		Vector2f texCoord;
		Vector3f normal;
		Vector3f binormal;
		Vector3f tangent;

		VertexPositionUVNormalBinormalTangent()
			: position(), texCoord(), normal(), binormal(), tangent()
		{}

		VertexPositionUVNormalBinormalTangent(
			const Vector3f& position,
			const Vector2f& texCoord,
			const Vector3f& normal,
			const Vector3f& binormal,
			const Vector3f& tangent)
			: position(position),
			texCoord(texCoord),
			normal(normal),
			binormal(binormal),
			tangent(tangent)
		{}

	};
}

#endif