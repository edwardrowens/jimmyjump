#include "Object.h"

// Position constructor
Object::Object(b2Body* objectBody, Character character) :
objectBody(objectBody),
isRenderable(true),
character(character),
group(CharacterGroup::OBJECT),
lastDrawnPosition(Box2dService::retrieveTopLeftVertex(*objectBody)) {
	Object::load(character);

	b2Vec2 objectPosition = Box2dService::retrieveTopLeftVertex(*objectBody);
	b2Vec2 screenCoords = CoordinateService::worldToScreen(objectPosition.x, objectPosition.y);
	objectRect.x = screenCoords.x;
	objectRect.y = screenCoords.y;

	objectRect.w = getBox2dWidth() * WorldConstants::PIXELS_PER_METER;
	objectRect.h = getBox2dHeight() * WorldConstants::PIXELS_PER_METER;

	objectBody->SetUserData(this);
}


// copy
Object::Object(const Object &object) :
objectBody(object.getBody()),
texture(object.getTexture()),
isRenderable(true),
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
	return Box2dService::retrieveTopLeftVertex(*objectBody).y - Box2dService::retrieveBottomLeftVertex(*objectBody).y;
}


float32 Object::getBox2dWidth() const {
	return Box2dService::retrieveTopRightVertex(*objectBody).x - Box2dService::retrieveTopLeftVertex(*objectBody).x;
}


int Object::getX() const {
	return objectRect.x;
}


int Object::getY() const {
	return objectRect.y;
}


int Object::getWidth() const {
	return objectRect.w;
}


int Object::getHeight() const {
	return objectRect.h;
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


CharacterGroup Object::getGroup() const {
	return group;
}


void Object::setCharacter(const Character& character) {
	this->character = character;
}


void Object::setIsRenderable(const bool& isRenderable) {
	this->isRenderable = isRenderable;
}


void Object::setContext(SDL_Renderer* context) {
	if (context == nullptr) {
		PrintErrors("The context passed into a level object was null.");
	}
	this->context = context;
}


void Object::setTexturePath(const std::string &texturePath) {
	previousTexturePath = this->texturePath;
	this->texturePath = texturePath;
}


void Object::setTexture(SDL_Texture* texture){
	this->texture = texture;
}


SDL_Texture* Object::getTexture() const {
	return texture;
}


std::string Object::getPreviousTexturePath() const {
	return previousTexturePath;
}


void Object::draw() {
	// This is the top left vertex of the box.
	b2Vec2 currentPosition = Box2dService::retrieveTopLeftVertex(*objectBody);

	// If there was a change in the object's physics, then update how it's rendered.
	if (currentPosition.x != lastDrawnPosition.x || currentPosition.y != lastDrawnPosition.y) {
		b2Vec2 displacement = CoordinateService::displacementFromWorldToScreen(lastDrawnPosition, currentPosition);
		objectRect.x += roundf(displacement.x);
		objectRect.y -= roundf(displacement.y);
		lastDrawnPosition = currentPosition;
	}

	// debug shit <>
	SDL_SetRenderDrawColor(context, 255, 0, 0, 255);
	SDL_RenderDrawLine(context, objectRect.x, objectRect.y, objectRect.x + objectRect.w, objectRect.y);
	SDL_RenderDrawLine(context, objectRect.x, objectRect.y, objectRect.x, objectRect.y + objectRect.h);
	SDL_RenderDrawLine(context, objectRect.x, objectRect.y + objectRect.h, objectRect.x + objectRect.w, objectRect.y + objectRect.h);
	SDL_RenderDrawLine(context, objectRect.x + objectRect.w, objectRect.y + objectRect.h, objectRect.x + objectRect.w, objectRect.y);

	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size
	SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, std::string("(" + std::to_string(objectRect.x) + ", " + std::to_string(objectRect.y) + ")").c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(context, surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = objectRect.x;  //controls the rect's x coordinate 
	Message_rect.y = objectRect.y - 10; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect
	SDL_RenderCopy(context, Message, NULL, &Message_rect);
	//</>

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