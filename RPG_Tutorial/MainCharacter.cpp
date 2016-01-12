#include "MainCharacter.h"


MainCharacter::MainCharacter() : MovableObject()
{
}

MainCharacter::~MainCharacter()
{
}

MainCharacter::MainCharacter(Position position, Character character): MovableObject(position, character){

}
