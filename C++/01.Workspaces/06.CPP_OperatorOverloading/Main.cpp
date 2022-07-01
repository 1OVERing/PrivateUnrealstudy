#include <iostream>

class vector2
{
public:
	float x, y;



	vector2 Add(const vector2& other) const
	{
		return vector2(x + other.x, y + other.y);
	}
	vector2 operator+ (const vector2& other) const
	{
		return vector2(x + other.x, y + other.y);
	}
	vector2 Multply(const vector2& other) const
	{
		return vector2(x * other.x, y * other.y);
	}
	vector2 operator*(const vector2& other) const
	{
		return vector2(x * other.x, y * other.y);
	}

public:
	vector2(float x, float y) : x(x), y(y){}
	~vector2(){}
};

std::ostream& operator<<(std::ostream& stream, const vector2& other)
{
	stream << other.x << ',' << other.y << std::endl;
	return stream;
}

int main()
{
	vector2 position(2.f, 5.f);
	vector2 speed(0.3f, 0.f);
	vector2 powerup(1.f, -2.f);


	vector2 result = position + (speed * powerup);
	std::cout << result << std::endl;


	return 0;
}