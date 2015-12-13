#include "Utility.h"


Utility::Utility(){
	createCharacterFileMap();
	// map that contains how many of what characters are currently in the level
	initializeAmountOfObjects(); 
}


Utility::~Utility(){
}

/*
Create enum to character file path mapping.
*/
void Utility::createCharacterFileMap(){
	characterFileMap[Character::BACKGROUND] = TEXTURE_PATH + "Background.png";
	characterFileMap[Character::FLYING_HEART_SMALL] = TEXTURE_PATH + "Characters/FlyingHeartSmall/Textures/FlyingHeartSmall";
	characterFileMap[Character::FLYING_HEART_LARGE] = TEXTURE_PATH + "Character/FlyingHeartLarge/Textures/FlyingHeartLarge";
	characterFileMap[Character::JIM] = TEXTURE_PATH + "Characters/Jimmy/Textures";
	characterFileMap[Character::LIGHT_GRAY_PLATFORM] = TEXTURE_PATH + "Platform/LandPiece_LightGray";
	characterFileMap[Character::LIGHT_GREEN_PLATFORM] = TEXTURE_PATH + "Platform/LandPiece_LightGreen";
	characterFileMap[Character::NONE] = "";
}

std::map<Character, std::string> Utility::getCharacterToFileMap() const{
	return characterFileMap;
}

void Utility::loadAllCharacterTextures(){

}

std::list<std::string> Utility::findAllPngs(std::string directory){
	std::list<std::string> pngs;
	std::list<std::string>::iterator it;
	it = pngs.begin();
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(directory.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			std::string fileName = ent->d_name;
			if (fileName.size() > 4){
				if (fileName.substr(fileName.size() - 4, 4) == ".png"){
					pngs.push_front(fileName);
				}
			}
		}
		closedir(dir);
		return pngs;
	}
	else {
		/* could not open directory */
		PrintErrors("Directory: " + directory + " could not be found.");
	}
}

void Utility::initializeAmountOfObjects(){
	// populate the map if it hasn't been done yet.
	if (amountOfObjects.size() == 0){
		for (int i = Character::BEGINNING + 1; i < Character::END; ++i){
			Character cmp = (Character) i;
			amountOfObjects[cmp] = 0;
		}
	}
}

void Utility::deleteTextures(Character character){
	if (amountOfObjects[character] > 0){
		PrintErrors("A character with " + std::to_string(amountOfObjects[character]) + " was going to be removed from the cache");
	}
	if (character == Character::NONE){
		return;
	}
	else{
		std::list<std::string> pngs = findAllPngs(characterFileMap[character]);
		for (std::string file : pngs){
			delete textureCache[characterFileMap[character] + file];
			textureCache.erase(characterFileMap[character] + file);
		}
	}
}