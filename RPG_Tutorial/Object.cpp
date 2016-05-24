#include "Object.h"

// Position constructor
Object::Object(b2Body* objectBody, Character character) :
objectBody(objectBody),
isRenderable(true),
character(character),
group(CharacterGroup::OBJECT),
width(Box2dService::getNonSensorFixtureScreenWidth(*objectBody)),
height(Box2dService::getNonSensorFixtureScreenHeight(*objectBody)) {
	Object::load(character);

	b2Vec2 objectPosition = Box2dService::retrieveTopLeftVertex(*objectBody);
	b2Vec2 screenCoords = ConversionService::worldPointToScreenPoint(objectPosition);
	objectRect.x = screenCoords.x;
	objectRect.y = screenCoords.y;

	objectRect.w = width;
	objectRect.h = height;

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


bool Object::getIsMovable() const {
	return group == CharacterGroup::MOVABLE_OBJECT || group == CharacterGroup::MAIN_CHARACTER;
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
	debugger.setContext(context);
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
	// Adjust rendering rectangle given the non sensor fixture's rotation.
	b2Vec2 renderingRectangle = ConversionService::retrieveRenderingRectangleForNonSensorFixture(*objectBody, width, height);
	objectRect.x = renderingRectangle.x;
	objectRect.y = renderingRectangle.y;

	/*debugger.renderAllFixturesOnBody(*objectBody);
	debugger.renderRectangle(objectRect);*/

	if (texture == nullptr)
		PrintErrors("No texture has been loaded.", SDL_GetError);
	if (SDL_RenderCopyEx(context, texture, NULL, &objectRect, MathService::radiansToDegrees(objectBody->GetAngle()), NULL, SDL_FLIP_NONE))
		PrintErrors("Failed to render " + texturePath, SDL_GetError);
}


void Object::load(Character character) {
	this->character = character;
	previousTexturePath = texturePath = utility.getDefaultTexturePath(character);
	walkCycles = utility.findAllWalkCycleFiles(character);
}