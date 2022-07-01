#include <iostream>

// Actor
// Object - 물체 / 객체
// OOP - Object Oriented Programming ( 객체지향 )
// Object -> Game-Object / Actor
// 개체 -> Entity		개체를 추상화를 할 때
class Entity
{
protected:
	float X;
	float Y;

public:
	virtual void Move(int xAmount, int yAmount)
	{
		X += xAmount;
		Y += yAmount;
	}

	Entity() : X(0), Y(0)
	{}
	~Entity()
	{}
};

class Player : public Entity
{
public:
	const char* name;

	void Move(int xAmount, int yAmount) override
	{
		X += ++xAmount;
		Y += ++yAmount;
	}

	void  SetName(const char* Name)
	{
		name = Name;
	}

public:
	Player() : name(NULL)
	{}
	~Player()
	{}
};

int main()
{
	Player player;
	Entity* pEntity;
	pEntity = &player;
	pEntity->Move(0, 0);
	player.SetName("이호근");

	std::cin.get();
	return 0;
}