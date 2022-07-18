#include<iostream>
#include<string>
#include "RTTI.h"


int main()
{
	GamePlayer* entity1 = new GamePlayer();
	GameEntity* entity2 = new GameEntity();

	if (&entity1->RTTI() == &entity2->RTTI())
	{
		// 같은 클래스.
		std::cout << "같다.\n";
	}
	else
	{
		std::cout << "다르다.\n";
	}
}