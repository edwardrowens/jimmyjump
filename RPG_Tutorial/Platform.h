#pragma once
#include "Object.h"
#include "CharacterInformation.h"

// Class which stores all the information for stationary objects.
class Platform : public Object
{
public:
	// Constructors and destructor
	Platform();
	Platform(Position position, Character character);
	Platform(const Platform &platform);
	~Platform();

	// Operator overloads
	Platform& operator=(Platform &platform);
};

