#pragma once
#include "Character.h"
#include <map>
#include <hash_map>
#include <SDL2.0\SDL.h>
#include <dirent/dirent.h>
#include "Errors.h"
#include <list>
#include <set>
#include <regex>

//TODO - ADD ALL TEXTURES ASSOCIATED WITH A CHARACTER
using std::string;
using std::cout;
using std::endl;

class Object;
class Utility
{
public:
	Utility();
	~Utility();

	std::hash_map<string, SDL_Texture*> textureCache;
	std::map<Character, int> amountOfObjects;

	std::map<char, std::set<string>> findAllWalkCycleFiles(const Character& character);
	string getDefaultTexturePath(Character character);
	std::map<Character, string> getCharacterToFileMap() const;
	void deleteTextures(Character character);
private:
	std::map<Character, string> characterFileMap;
	void createCharacterFileMap();
	std::list<string> findAllPngs(string fileName);
	void loadAllCharacterTextures();
	void initializeAmountOfObjects();
	std::set<string> findPngsWithPrefix(string directory, string prefix);
	bool fileExists(string file);
	string findPng(string fileOrDirectory);
	bool isPng(string file);
	const string TEXTURE_PATH = "Textures/jimmyJump_pack/PNG/";

};

