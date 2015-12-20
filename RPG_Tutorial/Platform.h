#pragma once
#include "Object.h"
class Platform : public Object
{
public:
	Platform();
	Platform(Position position);

	Platform(const Platform &platform);
	Platform& operator=(Platform &platform);
	~Platform();
};

