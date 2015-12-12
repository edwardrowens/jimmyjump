#pragma once
#include "Character.h"
#include <map>
#include <hash_map>
#include <SDL2.0\SDL.h>
//TODO - ADD ALL TEXTURES ASSOCIATED WITH A CHARACTER
class Utility
{
public:
	Utility();
	~Utility();

	std::map<Character, std::string> getCharacterToFileMap() const;
	std::hash_map<std::string, SDL_Texture*> textureCache;

private:
	std::map<Character, std::string> characterFileMap;
	
	void createCharacterFileMap();
	const std::string TEXTURE_PATH = "Textures/jimmyJump_pack/PNG/";
};

