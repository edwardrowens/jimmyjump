#include "MainCharacter.h"


MainCharacter::MainCharacter() : MovableObject()
{
}

MainCharacter::~MainCharacter()
{
}

MainCharacter::MainCharacter(Position position, Character character) : MovableObject(position, character){

}

void MainCharacter::setMousePosition(const int x, const int y){
	mouseX = x;
	mouseY = y;

	bool faceChange = false;
	if (mouseX >= (position.x + position.w / 2)){
		if (face != "R")
			faceChange = true;
		face = "R";
	}
	else{
		if (face != "L")
			faceChange = true;
		face = "L";
	}

	// If the face changes and the character is not moving, they should still face the mouse. This is definitely not the best place
	// for this check.
	if (faceChange){
		int fileLoc = utility.getFileLocFromPath(texturePath);
		string file = texturePath.substr(fileLoc, texturePath.length() - 1);
		texturePath = texturePath.substr(0, fileLoc);
		texturePath = texturePath + face + file.substr(1, file.length()-1);
	}
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

void MainCharacter::draw(){
	if (texture == nullptr)
		PrintErrors("No texture has been loaded.", SDL_GetError);
	if (SDL_RenderCopy(context, texture, NULL, objectRect))
		PrintErrors("Failed to render " + texturePath, SDL_GetError);
}