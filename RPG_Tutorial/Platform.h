#pragma once
#include "Object.h"
class Platform : public Object
{
public:
	Platform();
	Platform(int x, int y, int width, int height);
	~Platform();
};

