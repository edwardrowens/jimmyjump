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
#include "Box2D\Box2D.h"
#include "CoordinateService.h"

using std::string;

class Object
{
public:
	// Constructors, destructor
	//Object();
	Object(b2Body* objectBody, Character character);
	Object(const Object &object);
	~Object();

	// Operator overloads
	Object& operator= (const Object &object);

	// Public fields

	// Getters
	int getX() const;
	int getY() const;
	int getHeight() const;
	int getWidth() const;
	bool getIsMovable() const;
	SDL_Texture* getTexture() const;
	std::string getTexturePath() const;
	SDL_Texture* getPreviousTexture() const;
	bool getIsRenderable() const;
	bool getIsPlatform() const;
	SDL_Rect* getHitbox() const;
	Character getCharacter() const;
	Position getPosition() const;
	b2Body* getBody() const;

	// Setters
	void setX(const int &x);
	void setY(const int &y);
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
	SDL_Rect* hitbox;
	Character character;
	SDL_Renderer* context;
	std::map<char, std::set<string>> walkCycles;
	Utility utility;
	b2Body* objectBody;
	b2Vec2 linearVelocity;
	int height, width;
	const float HITBOXMODIFIER = .93;

	// Protected functions
	void setObjectTexture();
	int getBox2dWidth() const;
	int getBox2dHeight() const;
};

