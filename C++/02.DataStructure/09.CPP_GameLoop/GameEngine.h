#pragma once
#include "Position.h"



class GameEngine
{

private:
	bool isGameEnd;
	Position PlayerPosition;
	unsigned long delayTime;

public:
	void Initialize();
	void Run();

	void Update(const Position& CurPos);
	void Render(const Position& CurPos);
	void PostRender(const Position& CurPos);

	bool IsValidPosition(int x, int y);
	bool IsValidPosition(const Position& CurPos);

	bool IsGameEnd() const
	{return isGameEnd;}
public:
	GameEngine(unsigned long delay = 100ul) : isGameEnd(false), delayTime(delay), PlayerPosition() {}
	~GameEngine() {}
};

