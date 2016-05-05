#include "Object.h"

// Position constructor
Object::Object(b2Body* objectBody, Character character) :
objectBody(objectBody),
isRenderable(true),
isPlatform(false),
hitbox(new SDL_Rect),
character(character) {
	Object::load(character);
}


// copy
Object::Object(const Object &object) :
objectBody(object.getBody()),
texture(object.getTexture()),
isRenderable(true),
isPlatform(false),
hitbox(new SDL_Rect),
character(object.getCharacter()) {
	objectBody = object.getBody();
	texturePath = utility.getDefaultTexturePath(object.getCharacter());
}


//assignment operator overload
Object& Object::operator= (const Object &object) {
	if (this == &object)
		return *this;

	texture = object.getTexture();
	objectBody = object.getBody();
	objectBody = object.getBody();

	texturePath = utility.getDefaultTexturePath(object.getCharacter());
	character = object.getCharacter();

	return *this;
}


//destructor
Object::~Object() {
}


int Object::getHeight() const {
	return objectBody->GetFixtureList()->GetAABB(0).GetExtents().y;
}


int Object::getWidth() const {
	return objectBody->GetFixtureList()->GetAABB(0).GetExtents().x;
}


int Object::getX() const {
	return objectBody->GetPosition().x;
}


int Object::getY() const {
	return objectBody->GetPosition().y;
}


bool Object::getIsMovable() const {
	return isMovable;
}


bool Object::getIsRenderable() const {
	return isRenderable;
}


SDL_Rect* Object::getHitbox() const {
	return hitbox;
}


Character Object::getCharacter() const {
	return character;
}


std::string Object::getTexturePath() const {
	return texturePath;
}


b2Body* Object::getBody() const {
	return objectBody;
}


void Object::setX(const int &x) {
}


void Object::setY(const int &y) {

}


void Object::setCharacter(const Character& character) {
	this->character = character;
}


void Object::setIsRenderable(const bool& isRenderable) {
	this->isRenderable = isRenderable;
}


void Object::setIsMovable(const bool& isMovable){
	this->isMovable = isMovable;
}


void Object::setIsPlatform(const bool& isPlatform) {
	this->isPlatform = isPlatform;
}


void Object::setContext(SDL_Renderer* context) {
	if (context == nullptr) {
		PrintErrors("The context passed into a level object was null.");
	}
	this->context = context;
}


void Object::setTexture(SDL_Texture* texture){
	this->texture = texture;
}


bool Object::getIsPlatform() const {
	return isPlatform;
}


SDL_Texture* Object::getTexture() const {
	return texture;
}


SDL_Texture* Object::getPreviousTexture() const {
	return previousTexture;
}


void Object::draw() {
	// set up the SDL rect based upon the physics rectangle.
	SDL_Rect* objectRect = nullptr;
	(*objectRect).x = getX();
	(*objectRect).y = getY();
	(*objectRect).w = getWidth() * 2;
	(*objectRect).h = getHeight() * 2;

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

void Object::load(Character character) {
	this->character = character;
	texturePath = utility.getDefaultTexturePath(character);
	walkCycles = utility.findAllWalkCycleFiles(character);
}