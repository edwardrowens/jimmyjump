#pragma once
#include "Character.h"
#include <map>
#include <hash_map>
#include <SDL2.0\SDL.h>
#include <dirent/dirent.h>
#include "Errors.h"
#include <list>
#include "Object.h"

//TODO - ADD ALL TEXTURES ASSOCIATED WITH A CHARACTER
class Utility
{
public:
	Utility();
	~Utility();

	std::map<Character, std::string> getCharacterToFileMap() const;
	std::hash_map<std::string, SDL_Texture*> textureCache;
	std::map<Character, int> amountOfObjects;

	// all objects (characters) that are currently loaded into memory
	std::list<Object*> levelObjects;

	void deleteTextures(Character character);
private:
	std::map<Character, std::string> characterFileMap;
	
	void createCharacterFileMap();
	std::list<std::string> findAllPngs(std::string fileName);
	void loadAllCharacterTextures();
	void initializeAmountOfObjects();

	const std::string TEXTURE_PATH = "Textures/jimmyJump_pack/PNG/";

};

