#include "Object.h"
using std::string;

// utility constructor
Object::Object() :
objectTexture(nullptr),
objectRect(new SDL_Rect),
isMovable(false),
isRenderable(true),
isPlatform(false),
hitbox(new SDL_Rect()),
character(Character::NONE){
	++utility.amountOfObjects[Character::NONE];
}

// position constructor
Object::Object(Position position) :
position(position),
isRenderable(true),
isPlatform(false),
hitbox(new SDL_Rect),
character(Character::NONE){
	objectRect = new SDL_Rect();
	objectRect->x = position.x;
	objectRect->y = position.y;
	objectRect->w = position.w;
	objectRect->h = position.h;

	createHitbox();
	++utility.amountOfObjects[Character::NONE];
}

// copy
Object::Object(const Object &object) :
position(object.getPosition()),
objectTexture(object.getObjectTexture()),
isRenderable(true),
isPlatform(false),
hitbox(new SDL_Rect),
character(object.getCharacter()){
	*(hitbox) = *(object.getHitbox());
	objectRect = new SDL_Rect;
	*objectRect = *(object.getSDLRect());
	texturePath = utility.getDefaultTexturePath(object.getCharacter());
	++utility.amountOfObjects[Character::NONE];
}

//assignment operator overload
Object& Object::operator= (const Object &object){
	if (this == &object)
		return *this;

	objectRect = new SDL_Rect;
	*objectRect = *(object.getSDLRect());
	objectTexture = object.getObjectTexture();
	position = object.getPosition();
	SDL_Rect* movableRect = object.getHitbox();
	hitbox->x = movableRect->x;
	hitbox->y = movableRect->y;
	hitbox->w = movableRect->w;
	hitbox->h = movableRect->h;

	texturePath = utility.getDefaultTexturePath(object.getCharacter());
	character = object.getCharacter();

	delete movableRect;
	++utility.amountOfObjects[Character::NONE];

	return *this;
}

//destructor
Object::~Object(){
}

int Object::getHeight() const{
	return position.h;
}

int Object::getWidth() const{
	return position.w;
}

int Object::getX() const{
	return position.x;
}

int Object::getY() const{
	return position.y;
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

Position Object::getPosition() const{
	return position;
}

void Object::setPosition(const Position& position){
	this->position = position;
}

void Object::setCharacter(const Character& character){
	this->character = character;
}

void Object::setIsRenderable(const bool& isRenderable){
	this->isRenderable = isRenderable;
}

void Object::setHeight(const int& height){
	this->position.h = height;
	objectRect->h = height;
	createHitbox();
}

void Object::setWidth(const int& width){
	this->position.w = width;
	objectRect->w = width;
	createHitbox();
}

void Object::setX(const int& x){
	this->position.x = x;
	objectRect->x = x;
	createHitbox();
}

void Object::setY(const int& y){
	this->position.y = y;
	objectRect->y = y;
	createHitbox();
}

void Object::setIsMovable(const bool& isMovable){
	this->isMovable = isMovable;
}

void Object::setObjectTexture(){
	if (context == nullptr){
		PrintErrors("The context was not set before loading an object. Call setContext before calling load on a newly created object.");
	}
	// cannot be found in map
	if (utility.textureCache.find(texturePath) == utility.textureCache.end()){
		objectTexture = IMG_LoadTexture(context, texturePath.c_str());
		if (objectTexture == NULL && isRenderable){
			PrintErrors(texturePath + " did not load properly! Make sure the path is correct.");
		}
		utility.textureCache.insert(std::pair<std::string, SDL_Texture*>(texturePath, objectTexture));
	}
	else{
		objectTexture = utility.textureCache[texturePath];
	}
}

void Object::setIsPlatform(const bool& isPlatform){
	this->isPlatform = isPlatform;
}

void Object::setContext(SDL_Renderer* context){
	if (context == nullptr){
		PrintErrors("The context passed into a level object was null.");
	}
	this->context = context;
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

void Object::draw(){
	if (objectTexture == nullptr)
		PrintErrors("No texture has been loaded. A texture must be set with the method: load.", SDL_GetError);
	if (SDL_RenderCopy(context, objectTexture, NULL, objectRect))
		PrintErrors("Failed to render " + texturePath, SDL_GetError);
}

// create a hitbox that is approximately HITBOXMODIFIER * object's rectangle
void Object::createHitbox(){
	if (position.w == 0 || !isRenderable){
		hitbox->x = position.x;
		hitbox->y = position.y;
		hitbox->w = position.w;
		hitbox->h = position.h;
		return;
	}
	float distance, r;
	distance = sqrt(pow(position.h, 2) + pow(position.w, 2)) * (1 - HITBOXMODIFIER);
	r = sqrt(1 + pow((position.h / position.w), 2));

	float dx = (distance / r);
	float dy = ((distance*(position.h / position.w)) / r);

	hitbox->x = position.x + dx;
	hitbox->y = position.y + dy;
	hitbox->w = (position.x + position.w) - dx - hitbox->x;
	hitbox->h = (position.y + position.h) - dy - hitbox->y;
}

void Object::load(Character character){
	this->character = character;
	texturePath = utility.getDefaultTexturePath(character);
	walkCycles = utility.findAllWalkCycleFiles(character);
	if (character == Character::NONE){
		--utility.amountOfObjects[Character::NONE];
	}
	++utility.amountOfObjects[character];
	setObjectTexture();
}

/*
Removes the object from the cache.

Must be called when an object leavs memory.
*/
void Object::destroy(){
	--utility.amountOfObjects[this->character];
	if (utility.amountOfObjects[this->character] <= 0){
		utility.deleteTextures(this->character);
	}

	delete objectRect;
	delete hitbox;
}