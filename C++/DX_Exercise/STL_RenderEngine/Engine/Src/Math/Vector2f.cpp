#include "Core.h"
#include "Vector2f.h"
#include <math.h>

namespace Ronnie
{
	Vector2f::Vector2f()
		: x(0.0f), y(0.0f)
	{
	}

	Vector2f::Vector2f(float x, float y)
		: x(x), y(y)
	{
	}

	Vector2f::Vector2f(const Vector2f& other)
		: Vector2f(other.x, other.y)
	{
	}

	Vector2f::~Vector2f()
	{
	}

	float Vector2f::Length()
	{
		return sqrtf( (x * x) + (y * y) );
	}

	// |A| Dot |B| = (x1, y1) Dot (x2, y2).
	// |A| * |B| * Cos(Theta).
	float Vector2f::Dot(const Vector2f& other)
	{
		return x * other.x + y * other.y;
	}

	Vector2f Vector2f::Normalized()
	{
		float length = Length();
		float _x = x / length;
		float _y = y / length;

		return Vector2f(_x, _y);
	}


	std::wstring Vector2f::ToString()
	{
		std::wstringstream stream;
		stream << "(" << x << ", " << y << ")";

		return stream.str();
	}

	std::string Vector2f::ToStringA()
	{
		std::stringstream stream;
		stream << "(" << x << ", " << y << ")";

		return stream.str();
	}

	Vector2f& Vector2f::operator=(const Vector2f& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2f& Vector2f::operator+(const Vector2f& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2f& Vector2f::operator+(const float& other)
	{
		x += other;
		y += other;

		return *this;
	}

	Vector2f& Vector2f::operator+=(const Vector2f& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2f& Vector2f::operator+=(const float& other)
	{
		x += other;
		y += other;

		return *this;
	}

	Vector2f& Vector2f::operator-(const Vector2f& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2f& Vector2f::operator-(const float& other)
	{
		x -= other;
		y -= other;

		return *this;
	}

	Vector2f& Vector2f::operator-=(const Vector2f& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2f& Vector2f::operator-=(const float& other)
	{
		x -= other;
		y -= other;

		return *this;
	}

	Vector2f& Vector2f::operator*(const Vector2f& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	Vector2f& Vector2f::operator*(const float& other)
	{
		x *= other;
		y *= other;

		return *this;
	}

	Vector2f& Vector2f::operator*=(const Vector2f& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	Vector2f& Vector2f::operator*=(const float& other)
	{
		x *= other;
		y *= other;

		return *this;
	}

	Vector2f& Vector2f::operator/(const Vector2f& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	Vector2f& Vector2f::operator/(const float& other)
	{
		x /= other;
		y /= other;

		return *this;
	}

	Vector2f& Vector2f::operator/=(const Vector2f& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	Vector2f& Vector2f::operator/=(const float& other)
	{
		x /= other;
		y /= other;

		return *this;
	}
}