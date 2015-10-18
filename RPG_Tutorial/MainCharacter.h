#pragma once
#include "MovableObject.h"

class MainCharacter: public MovableObject
{
public:
	MainCharacter();
	~MainCharacter();
	MainCharacter(int x, int y, int width, int height);
};

