#pragma once
#include <SDL2.0\SDL.h>
#include <string>
#include <SDL2.0\SDL_image.h>
#include "Errors.h"
#include "Character.h"
#include "Utility.h"
#include <list>
#include "Position.h"
#include <map>
#include <set>

using std::string;

class Object
{
public:
	Object();
	Object(Position position);
	Object(const Object &object);
	~Object();
	Object& operator= (const Object &object);

	void load(Character character);

	const float HITBOXMODIFIER = .93;

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	bool getIsMovable() const;
	SDL_Texture* getObjectTexture() const;
	std::string getTexturePath() const;
	SDL_Rect* getSDLRect() const;
	bool getIsRenderable() const;
	bool getIsPlatform() const;
	SDL_Rect* getHitbox() const;
	Character getCharacter() const;
	Position getPosition() const;

	void setX(const int& x);
	void setY(const int& y);
	void setWidth(const int& width);
	void setHeight(const int& height);
	void setTexturePath(const std::string& newTexturePath);
	void setIsMovable(const bool& isMovable);
	void setIsRenderable(const bool& isRenderable);
	void setIsPlatform(const bool& isPlatform);
	void setCharacter(const Character& character);
	void setContext(SDL_Renderer* context);
	void setPosition(const Position& position);

	void createHitbox();

	void die();
	virtual void draw();

protected:
	bool isMovable;
	bool isRenderable;
	bool isPlatform;
	SDL_Texture* objectTexture;
	std::string texturePath;
	SDL_Rect* objectRect;
	SDL_Rect* hitbox;
	Position position;
	Character character;
	SDL_Renderer* context;
	std::map<char, std::set<string>> walkCycles;

	void setObjectTexture();
	Utility utility;
};

