#include <iostream>

// Actor
// Object - ��ü / ��ü
// OOP - Object Oriented Programming ( ��ü���� )
// Object -> Game-Object / Actor
// ��ü -> Entity		��ü�� �߻�ȭ�� �� ��
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
	player.SetName("��ȣ��");

	std::cin.get();
	return 0;
}