#include<iostream>
#include<string>
#include "RTTI.h"


int main()
{
	GamePlayer* entity1 = new GamePlayer();
	GameEntity* entity2 = new GameEntity();

	if (&entity1->RTTI() == &entity2->RTTI())
	{
		// ���� Ŭ����.
		std::cout << "����.\n";
	}
	else
	{
		std::cout << "�ٸ���.\n";
	}
}