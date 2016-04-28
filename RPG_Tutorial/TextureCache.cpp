#include "TextureCache.h"


TextureCache::TextureCache() {
	initializeAmountOfObjects();
}


TextureCache::~TextureCache() {}


void TextureCache::setContext(SDL_Renderer* context) {
	this->context = context;
}


/*
Looks at the object's path and checks if that texture has been loaded into the cache, if it has,
then we grab that texture and set it on the object. Otherwise, we load the texture given the object's
path and add the texture to the cache. Essentially, the object dictates its texture by manipulating only
its file path.
*/
void TextureCache::lockTextureForObject(Object &object) {
	if (context == nullptr){
		PrintErrors("The context passed in was null. A texture cannot be set without a context.");
	}

	if (object.getCharacter() == Character::BACKGROUND && amountOfObjects[Character::BACKGROUND] != 0)
		PrintErrors("A background is being added to the cache. Only a single background can exist per context. Currently there are " + std::to_string(amountOfObjects[Character::BACKGROUND]) + " backgrounds.");

	++amountOfObjects[object.getCharacter()];

	object.setContext(context);
	
	object.setTexture(addTextureToCache(object.getTexturePath()));
}


/*
Check if the object's texture path is not in the cache, if it isn't, load it and add it to the cache.
Otherwise, just set the object's texture to be the matched value in the cache.
*/
SDL_Texture* TextureCache::addTextureToCache(std::string texturePath) {
	if (textureCache.find(texturePath) == textureCache.end()) {
		SDL_Texture* texture = IMG_LoadTexture(context, texturePath.c_str());

		if (texture == nullptr)
			PrintErrors(texturePath + " did not load properly! Make sure the path is correct.");

		textureCache.insert(std::pair<std::string, SDL_Texture*>(texturePath, texture));

		return texture;
	}
	else{
		return textureCache[texturePath];
	}
}


void TextureCache::removeObjectFromCache(Object& object) {
	--amountOfObjects[object.getCharacter()];
	if (amountOfObjects[object.getCharacter()] <= 0)
		removeTextureFromCache(object.getCharacter());
}


void TextureCache::removeTextureFromCache(Character character) {
	if (amountOfObjects[character] <= 0){
		PrintErrors("A character with " + std::to_string(amountOfObjects[character]) + " associated textures were going to be removed from the cache");
	}
	if (character == Character::NONE) {
		return;
	}
	else if (utility.isPng(utility.getCharacterToFileMap()[character])) {
		SDL_DestroyTexture(textureCache[utility.getCharacterToFileMap()[character]]);
		textureCache.erase(utility.getCharacterToFileMap()[character]);
	}
	else {
		std::list<string> pngs = utility.findAllPngs(utility.getCharacterToFileMap()[character]);
		for (string file : pngs) {
			SDL_DestroyTexture(textureCache[utility.getCharacterToFileMap()[character] + file]);
			textureCache.erase(utility.getCharacterToFileMap()[character] + file);
		}
	}
}


/*
Map that keeps track of the amount of a characters in the current level.
*/
void TextureCache::initializeAmountOfObjects() {
	for (int i = Character::BEGINNING + 1; i < Character::END; ++i){
		Character cmp = (Character)i;
		amountOfObjects[cmp] = 0;
	}
}