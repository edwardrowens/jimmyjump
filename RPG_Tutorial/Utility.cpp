#include "Utility.h"

Utility::Utility(){
	createCharacterFileMap();
}

Utility::~Utility(){
}

/*
Create enum to character file path mapping. If this mapping ends with a file extension, that file will be the default
texture for that character.
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

std::list<string> Utility::findAllPngs(string directory){
	std::list<string> pngs;
	std::list<string>::iterator it = pngs.begin();
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(("./"+directory).c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			string fileName = ent->d_name;
			if (fileName.size() > 4){
				if (isPng(fileName)){
					pngs.push_back(fileName);
				}
			}
		}
		closedir(dir);
		if (pngs.size() <= 0){
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
	if (isPng(directory) || directory == ""){
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

	// If the character is tied to a single image, simply list that image as both the right and left direction walkcycles.
	if (isPng(characterFileMap[character])){
		rightAndLeftFiles['R'] = { characterFileMap[character] };
		rightAndLeftFiles['L'] = { characterFileMap[character] };
		return rightAndLeftFiles;
	}
	rightAndLeftFiles['R'] = findPngsWithPrefix(characterFileMap[character], "R");
	rightAndLeftFiles['L'] = findPngsWithPrefix(characterFileMap[character], "L");

	/*
	iterate through all keys of the map and then iterate through the value (set of strings)
	and check if any string matches the regular expression. If they don't, remove them from the
	set. This is used to eliminate all PNGs that are not apart of a walkcycle.
	*/
	std::map<char, std::set<string>>::iterator it = rightAndLeftFiles.begin();
	for (it; it != rightAndLeftFiles.end(); ){
		std::set<string>::iterator setIt = it->second.begin();
		for (setIt; setIt != it->second.end(); ){
			if (!std::regex_match(*setIt, std::regex(".[0-9].+"))){
				setIt = it->second.erase(setIt);
				if (it->second.empty()){
					break;
				}
			}
			else{
				++setIt;
			}
		}
		if (it->second.empty()){
			it = rightAndLeftFiles.erase(it);
			if (rightAndLeftFiles.empty()){
				PrintErrors("No valid walkcycles were found for " + characterFileMap[character]);
			}
		}
		else{
			++it;
		}
	}

	return rightAndLeftFiles;
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

// POTENITIAL PROBLEM: This is not OS-agnostic (probably idk, im not a scientist)
/*
Grabs the index of the actual file name from the path.
*/
int Utility::getFileLocFromPath(const string& filePath){
	int index = filePath.size() - 1;
	for (int i = index; i != 0 && filePath[i] != '/' && filePath[i] != '\\'; --i){
		index = i;
	}
	return index;
}