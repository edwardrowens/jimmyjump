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
	virtual string moveLeft();
	virtual string moveRight();
	void setMousePosition(const int x, const int y);
private:
	int mouseX, mouseY;
	string face;
};

