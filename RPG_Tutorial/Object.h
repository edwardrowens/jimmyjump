#pragma once
#include <SDL2.0\SDL.h>
#include <string>
#include <SDL2.0\SDL_image.h>
#include "Errors.h"
#include "Character.h"
#include "Utility.h"

class Object
{
public:
	Object();
	Object(int x, int y, int width, int height);
	Object(const Object &object);
	~Object();
	Object& operator= (const Object &object);

	void load(Character character, SDL_Renderer* context);

	const float HITBOX_MODIFIER = .93;

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

	void setX(const int& x);
	void setY(const int& y);
	void setWidth(const int& width);
	void setHeight(const int& height);
	void setObjectTexture(SDL_Renderer* context);
	void setTexturePath(const std::string& newTexturePath);
	void setIsMovable(const bool& isMovable);
	void setIsRenderable(const bool& isRenderable);
	void setIsPlatform(const bool& isPlatform);
	void setCharacter(const Character& character);

	void createHitbox();

	void die();
	virtual void draw(SDL_Renderer* context);

protected:
	int _x, _y, _width, _height;
	bool _isMovable;
	bool _isRenderable;
	bool _isPlatform;
	SDL_Texture* _objectTexture;
	/*std::string _currentTexturePath;
	std::string _previousTexturePath;*/
	SDL_Rect* _objectRect;
	SDL_Rect* _hitbox;
	Character _character;

	Utility utility;
};

