#pragma once
#include <SDL2.0\SDL.h>
#include <string>
#include <SDL2.0\SDL_image.h>
#include "Errors.h"

class Object
{
public:
	Object();
	Object(int x, int y, int width, int height);
	
	Object(const Object &object);
	~Object();
	Object& operator= (const Object &object);

	const std::string TEXTURE_PATH;
	const float HITBOX_MODIFIER = .95;

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

	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
	void setObjectTexture(SDL_Renderer* context, std::string texturePath);
	void setTexturePath(std::string newTexturePath);
	void setIsMovable(bool isMovable);
	void setIsRenderable(bool isRenderable);
	void setIsPlatform(bool isPlatform);

	void createHitbox();

	void die();
	virtual void draw(SDL_Renderer* context);

protected:
	int _x, _y, _width, _height;
	bool _isMovable;
	bool _isRenderable;
	bool _isPlatform;
	SDL_Texture* _objectTexture;
	std::string _currentTexturePath;
	std::string _previousTexturePath;
	SDL_Rect* _objectRect;
	SDL_Rect* _hitbox;
};

