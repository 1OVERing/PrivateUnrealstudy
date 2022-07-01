#include <iostream>

void Log(int value)
{
	std::cout << value << std::endl;
}

struct PlayerData
{
	int PlayerState;
};
class Player
{
private:
protected:
public:
	int X;
	int Y;
	// Amount = ¾ç/¼ö·®
	void Move(int xAmount, int yAmount)
	{
		X += xAmount;
		Y += yAmount;
	}


	Player() : X(0),Y(0)
	{}
	~Player()
	{}
};


int main()
{
	Player Player;
	Player.X = 10;
	Player.Move(0, 0);
	return 0;
}