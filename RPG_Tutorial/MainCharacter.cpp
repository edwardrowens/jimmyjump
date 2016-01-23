#include "MainCharacter.h"


MainCharacter::MainCharacter() : MovableObject()
{
}

MainCharacter::~MainCharacter()
{
}

MainCharacter::MainCharacter(Position position, Character character): MovableObject(position, character){

}

void MainCharacter::setMousePosition(const int x, const int y){
	mouseX = x;
	mouseY = y;

	if (mouseX >= position.x)
		face = "R";
	else
		face = "L";
}

string MainCharacter::moveLeft(){
	setX(position.x -= speed);
	if (currentMovement == Movements::RIGHT || stepCount >= walkCycles[face[0]].size()){
		stepCount = 0;
	}

	// POTENTIAL PROBLEM: If I use another type of file for textures, I would have to make a more general solution rather than
	// hard-coding this string.
	currentMovement = Movements::LEFT;
	texturePath = texturePath.substr(0, utility.getFileLocFromPath(texturePath));
	texturePath = texturePath + face + std::to_string(stepCount) + ".png";
	++stepCount;

	return texturePath;
}

string MainCharacter::moveRight(){
	setX(position.x += speed);
	if (currentMovement == Movements::LEFT || stepCount >= walkCycles[face[0]].size()){
		stepCount = 0;
	}

	// POTENTIAL PROBLEM: If I use another type of file for textures, I would have to make a more general solution rather than
	// hard-coding this string.
	currentMovement = Movements::RIGHT;
	texturePath = texturePath.substr(0, utility.getFileLocFromPath(texturePath));
	texturePath = texturePath + face + std::to_string(stepCount) + ".png";
	++stepCount;

	return texturePath;
}