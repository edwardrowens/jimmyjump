#include "Object.h"
using std::string;

//// Default constructor
//Object::Object() :
//texture(nullptr),
//objectRect(new SDL_Rect),
//isMovable(false),
//isRenderable(true),
//isPlatform(false),
//hitbox(new SDL_Rect()),
//character(Character::NONE){
//}

// Position constructor
Object::Object(b2Body* objectBody, Character character) :
objectBody(objectBody),
isRenderable(true),
isPlatform(false),
hitbox(new SDL_Rect),
character(character){
	objectRect = new SDL_Rect;
	objectRect->x = objectBody->GetPosition().x;
	objectRect->y = objectBody->GetPosition().y;
	objectRect->w = objectBody->GetFixtureList()->GetAABB(0).GetExtents().x;
	objectRect->h = objectBody->GetFixtureList()->GetAABB(0).GetExtents().y;

	createHitbox();
	Object::load(character);
}

// copy
Object::Object(const Object &object) :
objectBody(object.getBody()),
texture(object.getTexture()),
isRenderable(true),
isPlatform(false),
hitbox(new SDL_Rect),
character(object.getCharacter()){
	objectBody = object.getBody();
	objectRect = new SDL_Rect;
	*objectRect = *(object.getSDLRect());
	texturePath = utility.getDefaultTexturePath(object.getCharacter());
}

//assignment operator overload
Object& Object::operator= (const Object &object){
	if (this == &object)
		return *this;

	objectRect = new SDL_Rect;
	*objectRect = *(object.getSDLRect());
	texture = object.getTexture();
	objectBody = object.getBody();
	objectBody = object.getBody();

	texturePath = utility.getDefaultTexturePath(object.getCharacter());
	character = object.getCharacter();

	return *this;
}

//destructor
Object::~Object(){
	delete objectRect;
	delete hitbox;
}

int Object::getHeight() const{
	return objectRect->h;
}

int Object::getWidth() const{
	return objectRect->w;
}

int Object::getX() const{
	return objectRect->x;
}

int Object::getY() const{
	return objectRect->y;
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

b2Body* Object::getBody() const {
	return objectBody;
}

void Object::setCharacter(const Character& character){
	this->character = character;
}

void Object::setIsRenderable(const bool& isRenderable){
	this->isRenderable = isRenderable;
}

void Object::setHeight(const int& height){
	objectRect->h = height;
}

void Object::setWidth(const int& width){
	objectRect->w = width;
}

void Object::setX(const int& x){
	objectRect->x = x;
}

void Object::setY(const int& y){
	objectRect->y = y;
}

void Object::setIsMovable(const bool& isMovable){
	this->isMovable = isMovable;
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

void Object::setTexture(SDL_Texture* texture){
	this->texture = texture;
}

bool Object::getIsPlatform() const{
	return isPlatform;
}

SDL_Rect* Object::getSDLRect() const{
	return objectRect;
}

SDL_Texture* Object::getTexture() const{
	return texture;
}

SDL_Texture* Object::getPreviousTexture() const{
	return previousTexture;
}

void Object::draw(){
	if (texture == nullptr)
		PrintErrors("No texture has been loaded.", SDL_GetError);
	if (SDL_RenderCopy(context, texture, NULL, objectRect))
		PrintErrors("Failed to render " + texturePath, SDL_GetError);
}

//// create a hitbox that is approximately HITBOXMODIFIER * object's rectangle
//void Object::createHitbox(){
//	if (position.w == 0 || !isRenderable){
//		hitbox->x = position.x;
//		hitbox->y = position.y;
//		hitbox->w = position.w;
//		hitbox->h = position.h;
//		return;
//	}
//	float distance, r;
//	distance = sqrt(pow(position.h, 2) + pow(position.w, 2)) * (1 - HITBOXMODIFIER);
//	r = sqrt(1 + pow((position.h / position.w), 2));
//
//	float dx = (distance / r);
//	float dy = ((distance*(position.h / position.w)) / r);
//
//	hitbox->x = position.x + dx;
//	hitbox->y = position.y + dy;
//	hitbox->w = (position.x + position.w) - dx - hitbox->x;
//	hitbox->h = (position.y + position.h) - dy - hitbox->y;
//}

void Object::load(Character character){
	this->character = character;
	texturePath = utility.getDefaultTexturePath(character);
	walkCycles = utility.findAllWalkCycleFiles(character);
}