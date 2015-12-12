#include "Object.h"

// default
Object::Object() : _x(0), _y(0), _width(0), _height(0), _objectTexture(nullptr),  _objectRect(new SDL_Rect)
, _isMovable(false), _isRenderable(true), _isPlatform(false), _hitbox(new SDL_Rect()),
_character(Character::NONE){
}

// copy
Object::Object(const Object &object) : _x(object.getX()), _y(object.getY()), _width(object.getWidth()), _height(object.getHeight())
, _objectTexture(object.getObjectTexture()), _isRenderable(true), _isPlatform(false), _hitbox(new SDL_Rect),
_character(object.getCharacter()){
	*(_hitbox) = *(object.getHitbox());
	_objectRect = new SDL_Rect;
	*_objectRect = *(object.getSDLRect());
}

// coordinate constructor
Object::Object(int x, int y, int width, int height) : _x(x), _y(y), _width(width), _height(height)
,  _isRenderable(true), _isPlatform(false), _hitbox(new SDL_Rect), _character(Character::NONE){
	_objectRect = new SDL_Rect();
	_objectRect->x = _x;
	_objectRect->y = _y;
	_objectRect->w = _width;
	_objectRect->h = _height;

	createHitbox();
}

//assignment operator overload
Object& Object::operator= (const Object &object){
	if (this == &object)
		return *this;

	_objectRect = new SDL_Rect;
	*_objectRect = *(object.getSDLRect());
	_objectTexture = object.getObjectTexture();
	_x = object.getX();
	_y = object.getY();
	_width = object.getWidth();
	_height = object.getHeight();
	SDL_Rect* movableRect = object.getHitbox();
	this->_hitbox->x = movableRect->x;
	this->_hitbox->y = movableRect->y;
	this->_hitbox->w = movableRect->w;
	this->_hitbox->h = movableRect->h;

	_character = object.getCharacter();

	delete movableRect;

	return *this;
}

//destructor
Object::~Object(){
	delete _objectRect;
	delete _hitbox;
}

int Object::getHeight() const{
	return _height;
}

int Object::getWidth() const{
	return _width;
}

int Object::getX() const{
	return _x;
}

int Object::getY() const{
	return _y;
}

bool Object::getIsMovable() const{
	return _isMovable;
}

bool Object::getIsRenderable() const{
	return _isRenderable;
}

SDL_Rect* Object::getHitbox() const{
	return _hitbox;
}

Character Object::getCharacter() const{
	return _character;
}

void Object::setCharacter(const Character& character){
	_character = character;
}

void Object::setIsRenderable(const bool& isRenderable){
	_isRenderable = isRenderable;
}

void Object::setHeight(const int& height){
	_height = height;
	_objectRect->h = _height;
	createHitbox();
}

void Object::setWidth(const int& width){
	_width = width;
	_objectRect->w = _width;
	createHitbox();
}

void Object::setX(const int& x){
	_x = x;
	_objectRect->x = _x;
	createHitbox();
}

void Object::setY(const int& y){
	_y = y;
	_objectRect->y = _y;
	createHitbox();
}

void Object::setIsMovable(const bool& isMovable){
	_isMovable = isMovable;
}

void Object::setObjectTexture(SDL_Renderer* context){
	// cannot be found in map
	if (utility.textureCache.find(utility.getCharacterToFileMap()[_character]) == utility.textureCache.end()){
		_objectTexture = IMG_LoadTexture(context, utility.getCharacterToFileMap()[_character].c_str());
		utility.textureCache.insert(std::pair<std::string, SDL_Texture*>(utility.getCharacterToFileMap()[_character], _objectTexture));
	}
	else{
		_objectTexture = utility.textureCache[utility.getCharacterToFileMap()[_character]];
	}
}

void Object::setIsPlatform(const bool& isPlatform){
	_isPlatform = isPlatform;
}

bool Object::getIsPlatform() const{
	return _isPlatform;
}

SDL_Rect* Object::getSDLRect() const{
	return _objectRect;
}

SDL_Texture* Object::getObjectTexture() const{
	return _objectTexture;
}

void Object::draw(SDL_Renderer* context){
	if (_objectTexture == nullptr)
		PrintErrors("No texture has been loaded. A texture must be set with the method: load.", SDL_GetError);
	if (SDL_RenderCopy(context, _objectTexture, NULL, _objectRect))
		PrintErrors("Failed to render " + utility.getCharacterToFileMap()[_character], SDL_GetError);
}

// create a hitbox that is approximately HITBOX_MODIFIER * object's rectangle
void Object::createHitbox(){
	if (_width == 0 || !_isRenderable){
		_hitbox->x = _x;
		_hitbox->y = _y;
		_hitbox->w = _width;
		_hitbox->h = _height;
		return;
	}
	float distance, r;
	distance = sqrt(pow(_height,2) + pow(_width, 2)) * (1 - HITBOX_MODIFIER);
	r = sqrt(1 + pow((_height/_width),2));

	float dx = (distance / r);
	float dy = ((distance*(_height / _width)) / r);

	_hitbox->x = _x + dx;
	_hitbox->y = _y + dy;
	_hitbox->w = (_x + _width) - dx - _hitbox->x;
	_hitbox->h = (_y + _height) - dy - _hitbox->y;
}

void Object::load(Character character, SDL_Renderer* context){
	_character = character;
	setObjectTexture(context);
}