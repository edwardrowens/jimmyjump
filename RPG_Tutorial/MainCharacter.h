#pragma once
#include "MovableObject.h"

using std::string;

class MainCharacter: public MovableObject
{
public:
	// Constructors and destructor
	MainCharacter();
	~MainCharacter();
	MainCharacter(b2Body* objectBody, Character character);

	// Public functions
	void setMousePosition(const int x, const int y);
private:
	// Fields
	int mouseX, mouseY;
	string face;

	// Functions
	void moveLeft();
	void moveRight();
};

