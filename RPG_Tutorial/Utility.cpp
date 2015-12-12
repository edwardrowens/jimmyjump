#include "Utility.h"


Utility::Utility(){
	createCharacterFileMap();
}


Utility::~Utility(){
}

/*
Create enum to character file path mapping.
*/
void Utility::createCharacterFileMap(){
	characterFileMap[Character::BACKGROUND] = TEXTURE_PATH + "Background.png";
	characterFileMap[Character::FLYING_HEART_SMALL] = TEXTURE_PATH + "Characters/FlyingHeart/FlyingHeartSmall";
	characterFileMap[Character::FLYING_HEART_LARGE] = TEXTURE_PATH + "Character/FlyingHeart/FlyingHeartLarge";
	characterFileMap[Character::JIM] = TEXTURE_PATH + "Characters/Jimmy/Textures";
	characterFileMap[Character::LIGHT_GRAY_PLATFORM] = TEXTURE_PATH + "Platform/LandPiece_LightGray";
	characterFileMap[Character::LIGHT_GREEN_PLATFORM] = TEXTURE_PATH + "Platform/LandPiece_LightGreen";
	characterFileMap[Character::NONE] = "";
}

std::map<Character, std::string> Utility::getCharacterToFileMap() const{
	return characterFileMap;
}

void loadAllCharacterTextures(){

}