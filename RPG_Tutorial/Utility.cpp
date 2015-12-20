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
	characterFileMap[Character::FLYING_HEART_SMALL] = TEXTURE_PATH + "Characters/FlyingHeartSmall/Textures/";
	characterFileMap[Character::FLYING_HEART_LARGE] = TEXTURE_PATH + "Character/FlyingHeartLarge/Textures/";
	characterFileMap[Character::JIM] = TEXTURE_PATH + "Characters/Jimmy/Textures";
	characterFileMap[Character::LIGHT_GRAY_PLATFORM] = TEXTURE_PATH + "Platform/LandPiece_LightGray.png";
	characterFileMap[Character::LIGHT_GREEN_PLATFORM] = TEXTURE_PATH + "Platform/LandPiece_LightGreen.png";
	characterFileMap[Character::NONE] = "";
}

std::map<Character, string> Utility::getCharacterToFileMap() const{
	return characterFileMap;
}

void Utility::loadAllCharacterTextures(){

}

std::list<string> Utility::findAllPngs(string directory){
	std::list<string> pngs;
	std::list<string>::iterator it = pngs.begin();
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(directory.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			string fileName = ent->d_name;
			if (fileName.size() > 4){
				if (isPng(fileName)){
					pngs.push_back(fileName);
				}
			}
		}
		closedir(dir);
		if (pngs.size() >= 0){
			PrintErrors("No png files could be found in " + directory + ".");
		}
		return pngs;
	}
	else {
		/* could not open directory */
		PrintErrors("Directory: " + directory + " could not be found.");
	}
}

/*
@returns An ordered set of PNG files with the prefix.
*/
std::set<string> Utility::findPngsWithPrefix(string directory, string prefix){
	if (directory.substr(directory.size() - 4, 4) == ".png" || directory == ""){
		std::set<string> toReturn = { directory };
		return toReturn;
	}

	std::list<string> files = findAllPngs(directory);

	std::set<string> filesToFind;
	for (string file : files){
		if (file.substr(0, prefix.size()) == prefix){
			filesToFind.insert(file);
		}
	}

	return filesToFind;
}

std::map<char, std::set<string>> Utility::findAllWalkCycleFiles(const Character& character){
	std::map<char, std::set<string>> rightAndLeftFiles;
	rightAndLeftFiles['R'] = findPngsWithPrefix(characterFileMap[character], "R");
	rightAndLeftFiles['L'] = findPngsWithPrefix(characterFileMap[character], "L");

	/*
	iterate through all keys of the map and then iterate through the value (set of strings)
	and check if any string matches the regular expression. If they don't, remove them from the
	set. This is used to eliminate all PNGs that are not apart of a walkcycle.
	*/
	std::map<char, std::set<string>>::iterator it = rightAndLeftFiles.begin();
	for (it; it != rightAndLeftFiles.end(); ++it){
		for (string filePath : rightAndLeftFiles[it->first]){
			if (!std::regex_match(filePath, std::regex(".[0-9].+"))){
				rightAndLeftFiles[it->first].erase(rightAndLeftFiles[it->first].find(filePath));
			}
		}
	}

	return rightAndLeftFiles;
}

void Utility::initializeAmountOfObjects(){
	// populate the map if it hasn't been done yet.
	if (amountOfObjects.size() == 0){
		for (int i = Character::BEGINNING + 1; i < Character::END; ++i){
			Character cmp = (Character)i;
			amountOfObjects[cmp] = 0;
		}
	}
}

void Utility::deleteTextures(Character character){
	if (amountOfObjects[character] >= 0){
		PrintErrors("A character with " + std::to_string(amountOfObjects[character]) + " associated textures was going to be removed from the cache");
	}
	if (character == Character::NONE){
		return;
	}
	else{
		std::list<string> pngs = findAllPngs(characterFileMap[character]);
		for (string file : pngs){
			delete textureCache[characterFileMap[character] + file];
			textureCache.erase(characterFileMap[character] + file);
		}
	}
}

//Potential speed up is to simply manually add this to a map.
string Utility::getDefaultTexturePath(Character character){
	string defaultTextureDirectory = characterFileMap[character];

	// if the character is associated with a single PNG, set its default texture to it
	if (isPng(defaultTextureDirectory) || defaultTextureDirectory == ""){
		return defaultTextureDirectory;
	}
	// if the character has a walk cycle, they should have a standing facing right.
	else if (fileExists(defaultTextureDirectory + "/RStanding.png")){
		return defaultTextureDirectory + "/RStanding.png";
	}
	// if none of the others work, just find the first texture in the character's directory.
	else{
		return findPng(defaultTextureDirectory);
	}
}

// Faster way of finding if a file exists 
// http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c)
bool Utility::fileExists(string file){
	struct stat buffer;
	return (stat(file.c_str(), &buffer) == 0);
}

// Return the first file you find that's not the . or .. operator
string Utility::findPng(string directory){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(directory.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_name != "." && ent->d_name != ".." && isPng((string)ent->d_name)){
				return ent->d_name;
			}
		}
		PrintErrors("No textures are located in " + directory);
	}
	else {
		/* could not open directory */
		PrintErrors("Directory: " + directory + " could not be found.");
	}
}

bool Utility::isPng(string file){
	return file.substr(file.size() - 4, 4) == ".png";
}