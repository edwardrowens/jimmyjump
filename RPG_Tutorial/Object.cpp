#include "Object.h"

// Position constructor
Object::Object(b2Body* objectBody, Character character) :
objectBody(objectBody),
isRenderable(true),
isPlatform(false),
character(character),
previousPosition(retrieveTopLeftVertex()) {
	Object::load(character);

	b2Vec2 objectPosition = retrieveTopLeftVertex();
	b2Vec2 screenCoords = CoordinateService::worldToScreen(objectPosition.x, objectPosition.y);
	objectRect.x = screenCoords.x;
	objectRect.y = screenCoords.y;

	objectRect.w = getBox2dWidth() * WorldConstants::PIXELS_PER_METER;
	objectRect.h = getBox2dHeight() * WorldConstants::PIXELS_PER_METER;
}


// copy
Object::Object(const Object &object) :
objectBody(object.getBody()),
texture(object.getTexture()),
isRenderable(true),
isPlatform(false),
character(object.getCharacter()) {
	objectBody = object.getBody();
}


//assignment operator overload
Object& Object::operator= (const Object &object) {
	if (this == &object)
		return *this;

	texture = object.getTexture();
	objectBody = object.getBody();

	character = object.getCharacter();

	return *this;
}


//destructor
Object::~Object() {
}


float32 Object::getBox2dHeight() const {
	return retrieveTopLeftVertex().y - retrieveBottomLeftVertex().y;
}


float32 Object::getBox2dWidth() const {
	return retrieveTopRightVertex().x - retrieveTopLeftVertex().x;
}


int Object::getX() const {
	return objectRect.x;
}


int Object::getY() const {
	return objectRect.y;
}


int Object::getWidth() const {
	return width;
}


int Object::getHeight() const {
	return height;
}


bool Object::getIsMovable() const {
	return isMovable;
}


bool Object::getIsRenderable() const {
	return isRenderable;
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


void Object::setTexturePath(const std::string &texturePath) {
	previousTexturePath = texturePath;
	this->texturePath = texturePath;
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


std::string Object::getPreviousTexturePath() const {
	return previousTexturePath;
}


void Object::draw() {
	// This is the top left vertex of the box.
	b2Vec2 currentPosition = retrieveTopLeftVertex();

	// If there was a change in the object's physics, then update how it's rendered.
	if (currentPosition.x != previousPosition.x || currentPosition.y != previousPosition.y) {
		b2Vec2 displacement = CoordinateService::displacementFromWorldToScreen(previousPosition, currentPosition);
		objectRect.x += roundf(displacement.x);
		objectRect.y -= roundf(displacement.y);
		previousPosition = currentPosition;
	}

	if (texture == nullptr)
		PrintErrors("No texture has been loaded.", SDL_GetError);
	if (SDL_RenderCopy(context, texture, NULL, &objectRect))
		PrintErrors("Failed to render " + texturePath, SDL_GetError);
}


void Object::load(Character character) {
	this->character = character;
	previousTexturePath = texturePath = utility.getDefaultTexturePath(character);
	walkCycles = utility.findAllWalkCycleFiles(character);
}


b2Vec2 Object::retrieveTopLeftVertex() const {
	return objectBody->GetWorldPoint(dynamic_cast<b2PolygonShape*>(objectBody->GetFixtureList()->GetShape())->GetVertex(3));
}


b2Vec2 Object::retrieveBottomRightVertex() const {
	return objectBody->GetWorldPoint(dynamic_cast<b2PolygonShape*>(objectBody->GetFixtureList()->GetShape())->GetVertex(1));
}


b2Vec2 Object::retrieveBottomLeftVertex() const {
	return objectBody->GetWorldPoint(dynamic_cast<b2PolygonShape*>(objectBody->GetFixtureList()->GetShape())->GetVertex(0));
}


b2Vec2 Object::retrieveTopRightVertex() const {
	return objectBody->GetWorldPoint(dynamic_cast<b2PolygonShape*>(objectBody->GetFixtureList()->GetShape())->GetVertex(2));
}