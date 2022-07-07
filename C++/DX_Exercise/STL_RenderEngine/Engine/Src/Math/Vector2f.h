#pragma once

#ifndef _VECTOR2F_
#define _VECTOR2F_

#include "Core.h"

namespace Ronnie
{
	class ENGINE_API Vector2f
	{
	public:
		float x;
		float y;

		Vector2f();
		Vector2f(float x, float y);
		Vector2f(const Vector2f& other);
		~Vector2f();

		float Length();
		float Dot(const Vector2f& other);
		Vector2f Normalized();

		std::wstring ToString();
		std::string ToStringA();

		Vector2f& operator=(const Vector2f& other);

		Vector2f& operator+(const Vector2f& other);
		Vector2f& operator+(const float& other);
		Vector2f& operator+=(const Vector2f& other);
		Vector2f& operator+=(const float& other);

		Vector2f& operator-(const Vector2f& other);
		Vector2f& operator-(const float& other);
		Vector2f& operator-=(const Vector2f& other);
		Vector2f& operator-=(const float& other);

		Vector2f& operator*(const Vector2f& other);
		Vector2f& operator*(const float& other);
		Vector2f& operator*=(const Vector2f& other);
		Vector2f& operator*=(const float& other);

		Vector2f& operator/(const Vector2f& other);
		Vector2f& operator/(const float& other);
		Vector2f& operator/=(const Vector2f& other);
		Vector2f& operator/=(const float& other);
	};
}
#endif