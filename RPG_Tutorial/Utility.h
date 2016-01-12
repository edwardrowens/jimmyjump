#pragma once
#include "CharacterInformation.h"
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
	// Constructors and destructor
	Utility();
	~Utility();

	// Fields
	std::map<char, std::set<string>> findAllWalkCycleFiles(const Character& character);
	string getDefaultTexturePath(Character character);
	std::map<Character, string> getCharacterToFileMap() const;

	// Functions
	bool isPng(string file);
	std::list<string> findAllPngs(string fileName);

private:
	// Fields
	std::map<Character, string> characterFileMap;
	const string TEXTURE_PATH = "Textures/jimmyJump_pack/PNG/";

	// Functions
	void createCharacterFileMap();
	std::set<string> findPngsWithPrefix(string directory, string prefix);
	bool fileExists(string file);
	string findPng(string fileOrDirectory);

};

