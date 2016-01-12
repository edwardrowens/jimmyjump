#pragma once
#include "MovableObject.h"

class MainCharacter: public MovableObject
{
public:
	MainCharacter();
	~MainCharacter();
	MainCharacter(Position position, Character character);
};

