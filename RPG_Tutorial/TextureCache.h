#pragma once

#include "Object.h"
class TextureCache {
public:
	TextureCache(SDL_Renderer* context);
	~TextureCache();

	void removeObjectFromCache(Object& object);
	void lockTextureForObject(Object& object);

private:
	// Fields
	SDL_Renderer* context;
	// The full file path mapped to the SDL representation of the texture
	std::hash_map<string, SDL_Texture*> textureCache;
	std::map<Character, int> amountOfObjects;
	Utility utility;

	// Functions
	void initializeAmountOfObjects();
	void removeTextureFromCache(Character character);
	SDL_Texture* addTextureToCache(std::string texturePath);
};

