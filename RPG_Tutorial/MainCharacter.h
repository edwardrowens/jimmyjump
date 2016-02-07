#pragma once
#include "MovableObject.h"

using std::string;

class MainCharacter: public MovableObject
{
public:
	// Constructors and destructor
	MainCharacter();
	~MainCharacter();
	MainCharacter(Position position, Character character);

	// Public functions
	void setMousePosition(const int x, const int y);
private:
	// Fields
	int mouseX, mouseY;
	string face;

	// Functions
	virtual string moveLeft();
	virtual string moveRight();
};

