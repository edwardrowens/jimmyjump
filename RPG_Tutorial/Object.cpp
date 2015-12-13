#include "Object.h"

// default
Object::Object() : x(0), y(0), width(0), height(0), objectTexture(nullptr),  objectRect(new SDL_Rect)
, isMovable(false), isRenderable(true), isPlatform(false), hitbox(new SDL_Rect()),
character(Character::NONE){
	utility.levelObjects.push_back(this);
}

// copy
Object::Object(const Object &object) : x(object.getX()), y(object.getY()), width(object.getWidth()), height(object.getHeight())
, objectTexture(object.getObjectTexture()), isRenderable(true), isPlatform(false), hitbox(new SDL_Rect),
character(object.getCharacter()){
	*(hitbox) = *(object.getHitbox());
	objectRect = new SDL_Rect;
	*objectRect = *(object.getSDLRect());
	utility.levelObjects.push_back(this);
}

// coordinate constructor
Object::Object(int x, int y, int width, int height) : x(x), y(y), width(width), height(height)
,  isRenderable(true), isPlatform(false), hitbox(new SDL_Rect), character(Character::NONE){
	objectRect = new SDL_Rect();
	objectRect->x = x;
	objectRect->y = y;
	objectRect->w = width;
	objectRect->h = height;

	createHitbox();
	utility.levelObjects.push_back(this);
}

//assignment operator overload
Object& Object::operator= (const Object &object){
	if (this == &object)
		return *this;

	objectRect = new SDL_Rect;
	*objectRect = *(object.getSDLRect());
	objectTexture = object.getObjectTexture();
	x = object.getX();
	y = object.getY();
	width = object.getWidth();
	height = object.getHeight();
	SDL_Rect* movableRect = object.getHitbox();
	this->hitbox->x = movableRect->x;
	this->hitbox->y = movableRect->y;
	this->hitbox->w = movableRect->w;
	this->hitbox->h = movableRect->h;

	character = object.getCharacter();

	delete movableRect;
	utility.levelObjects.push_back(this);

	return *this;
}

//destructor
Object::~Object(){
	std::list<Object*>::iterator it;
	it = utility.levelObjects.begin();

	for (auto it : utility.levelObjects){
		if (it == this){
			utility.levelObjects.remove(it);
			break;
		}
	}

	--utility.amountOfObjects[this->character];
	if (utility.amountOfObjects[this->character] <= 0){
		utility.deleteTextures(utility.getCharacterToFileMap[this->character]);
	}

	delete objectRect;
	delete hitbox;
}

int Object::getHeight() const{
	return height;
}

int Object::getWidth() const{
	return width;
}

int Object::getX() const{
	return x;
}

int Object::getY() const{
	return y;
}

bool Object::getIsMovable() const{
	return isMovable;
}

bool Object::getIsRenderable() const{
	return isRenderable;
}

SDL_Rect* Object::getHitbox() const{
	return hitbox;
}

Character Object::getCharacter() const{
	return character;
}

std::string Object::getTexturePath() const{
	return texturePath;
}

void Object::setCharacter(const Character& character){
	this->character = character;
}

void Object::setIsRenderable(const bool& isRenderable){
	this->isRenderable = isRenderable;
}

void Object::setHeight(const int& height){
	this->height = height;
	objectRect->h = height;
	createHitbox();
}

void Object::setWidth(const int& width){
	this->width = width;
	objectRect->w = width;
	createHitbox();
}

void Object::setX(const int& x){
	this->x = x;
	objectRect->x = x;
	createHitbox();
}

void Object::setY(const int& y){
	this->y = y;
	objectRect->y = y;
	createHitbox();
}

void Object::setIsMovable(const bool& isMovable){
	this->isMovable = isMovable;
}

void Object::setObjectTexture(SDL_Renderer* context){
	// cannot be found in map
	if (utility.textureCache.find(texturePath) == utility.textureCache.end()){
		objectTexture = IMG_LoadTexture(context, texturePath.c_str());
		utility.textureCache.insert(std::pair<std::string, SDL_Texture*>(texturePath, objectTexture));
	}
	else{
		objectTexture = utility.textureCache[texturePath];
	}
}

void Object::setIsPlatform(const bool& isPlatform){
	this->isPlatform = isPlatform;
}

bool Object::getIsPlatform() const{
	return isPlatform;
}

SDL_Rect* Object::getSDLRect() const{
	return objectRect;
}

SDL_Texture* Object::getObjectTexture() const{
	return objectTexture;
}

void Object::draw(SDL_Renderer* context){
	if (objectTexture == nullptr)
		PrintErrors("No texture has been loaded. A texture must be set with the method: load.", SDL_GetError);
	if (SDL_RenderCopy(context, objectTexture, NULL, objectRect))
		PrintErrors("Failed to render " + texturePath, SDL_GetError);
}

// create a hitbox that is approximately HITBOXMODIFIER * object's rectangle
void Object::createHitbox(){
	if (width == 0 || !isRenderable){
		hitbox->x = x;
		hitbox->y = y;
		hitbox->w = width;
		hitbox->h = height;
		return;
	}
	float distance, r;
	distance = sqrt(pow(height,2) + pow(width, 2)) * (1 - HITBOXMODIFIER);
	r = sqrt(1 + pow((height/width),2));

	float dx = (distance / r);
	float dy = ((distance*(height / width)) / r);

	hitbox->x = x + dx;
	hitbox->y = y + dy;
	hitbox->w = (x + width) - dx - hitbox->x;
	hitbox->h = (y + height) - dy - hitbox->y;
}

void Object::load(Character character, SDL_Renderer* context){
	this->character = character;
	texturePath = utility.getCharacterToFileMap()[character];
	++utility.amountOfObjects[character];
	setObjectTexture(context);
}