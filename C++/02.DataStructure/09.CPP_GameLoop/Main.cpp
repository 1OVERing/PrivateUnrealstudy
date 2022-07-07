#include "../04.CPP_Stack/stack.h"
#include "Util.h"
#include "GameEngine.h"
#include <iostream>
int main()
{
	GameEngine* Engine = new GameEngine();

	Engine->Initialize();
	Engine->Run();

	delete Engine;
	std::cin.get();
}
