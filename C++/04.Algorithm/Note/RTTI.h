#pragma once
#include "macro.h"

class GameEntity
{
	RTTI_DECL

	GameEntity();
	~GameEntity();
/*
public:
	static const RTTI rtti;
	virtual const RTTI& RTTI() const { return rtti; }*/
};

class GamePlayer : public GameEntity
{
	GamePlayer();
	~GamePlayer();
};

