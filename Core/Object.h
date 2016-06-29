#ifndef _OBJECT_H
#define _OBJECT_H

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
#include "ConversionService.h"
#include "Box2dService.h"
#include <SDL2.0\SDL_ttf.h>
#include "Debugger.h"
#include "MathService.h"

using std::string;

class Object {
public:
	// Constructors, destructor
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
	SDL_Texture* getTexture() const;
	std::string getTexturePath() const;
	std::string getPreviousTexturePath() const;
	bool getIsRenderable() const;
	bool getIsMovable() const;
	Character getCharacter() const;
	b2Vec2 getPosition() const;
	b2Body* getBody() const;
	CharacterGroup getGroup() const;

	// Setters
	void setX(const int &x);
	void setY(const int &y);
	void setTexture(SDL_Texture* texture);
	void setIsRenderable(const bool& isRenderable);
	void setCharacter(const Character& character);
	void setContext(SDL_Renderer* context);

	// Public functions
	virtual void draw();
	void load(Character character);
	void setId(const uint32_t& id);
	uint32_t getId() const;

protected:
	// Protected fields
	bool isRenderable;
	SDL_Texture* texture;
	std::string previousTexturePath;
	Character character;
	SDL_Renderer* context;
	std::map<char, std::set<string>> walkCycles;
	Utility utility;
	b2Body* objectBody;
	b2Vec2 linearVelocity;
	CharacterGroup group;
	float32 width, height;
	SDL_Rect objectRect;
	bool isMovable;

	// Protected functions
	void setTexturePath(const std::string &texturePath);

private:
	// Fields
	std::string texturePath;
	Debugger debugger;
	double RADIANS_TO_DEGREES(float32 angle);
	uint32_t id;
};
#endif