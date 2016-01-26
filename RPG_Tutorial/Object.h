#pragma once
#include <SDL2.0\SDL.h>
#include <string>
#include <SDL2.0\SDL_image.h>
#include "Errors.h"
#include "CharacterInformation.h"
#include <list>
#include "Position.h"
#include <map>
#include <set>
#include "Utility.h"

using std::string;

class Object
{
public:
	// Constructors, destructor
	Object();
	Object(Position position, Character character);
	Object(const Object &object);
	~Object();

	// Operator overloads
	Object& operator= (const Object &object);

	// Public fields
	const float HITBOXMODIFIER = .93;

	// Getters
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	bool getIsMovable() const;
	SDL_Texture* getTexture() const;
	std::string getTexturePath() const;
	SDL_Texture* getPreviousTexture() const;
	SDL_Rect* getSDLRect() const;
	bool getIsRenderable() const;
	bool getIsPlatform() const;
	SDL_Rect* getHitbox() const;
	Character getCharacter() const;
	Position getPosition() const;

	// Setters
	void setX(const int& x);
	void setY(const int& y);
	void setWidth(const int& width);
	void setHeight(const int& height);
	void setTexturePath(const std::string& newTexturePath);
	void setTexture(SDL_Texture* texture);
	void setIsMovable(const bool& isMovable);
	void setIsRenderable(const bool& isRenderable);
	void setIsPlatform(const bool& isPlatform);
	void setCharacter(const Character& character);
	void setContext(SDL_Renderer* context);
	void setPosition(const Position& position);

	// Public functions
	void createHitbox();
	virtual void draw();
	void load(Character character);

protected:
	// Protected fields
	bool isMovable;
	bool isRenderable;
	bool isPlatform;
	SDL_Texture* texture;
	SDL_Texture* previousTexture;
	std::string texturePath;
	SDL_Rect* objectRect;
	SDL_Rect* hitbox;
	Position position;
	Character character;
	SDL_Renderer* context;
	std::map<char, std::set<string>> walkCycles;
	Utility utility;

	// Protected functions
	void setObjectTexture();
};

