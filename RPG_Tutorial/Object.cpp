#include "Object.h"


Object::Object() : _x(0), _y(0), _width(0), _height(0), _objectTexture(nullptr), _texturePath(""), _objectRect(new SDL_Rect)
, TEXTURE_PATH("Textures/jimmyJump_pack/PNG/"), _isMovable(false){
}

//copy constructor
Object::Object(const Object &object) : _x(object.getX()), _y(object.getY()), _width(object.getWidth()), _height(object.getHeight())
, _objectTexture(object.getObjectTexture()), _texturePath(object.getTexturePath()){
	_objectRect = new SDL_Rect;
	*_objectRect = *(object.getSDLRect());
}

//assignment operator overload
Object& Object::operator= (const Object &object){
	if (this == &object)
		return *this;

	_objectRect = new SDL_Rect;
	*_objectRect = *(object.getSDLRect());
	_objectTexture = object.getObjectTexture();
	_texturePath = object.getTexturePath();
	_x = object.getX();
	_y = object.getY();
	_width = object.getWidth();
	_height = object.getHeight();

	return *this;
}

//destructor
Object::~Object(){
	delete _objectRect;
}

Object::Object(int x, int y, int width, int height) : _x(x), _y(y), _width(width), _height(height)
, TEXTURE_PATH("Textures/jimmyJump_pack/PNG/"){
	_objectRect = new SDL_Rect();
	_objectRect->x = _x;
	_objectRect->y = _y;
	_objectRect->w = _width;
	_objectRect->h = _height;
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

void Object::setHeight(int height){
	this->_height = height;
	_objectRect->h = _height;
}

void Object::setWidth(int width){
	this->_width = width;
	_objectRect->w = _width;
}

void Object::setX(int x){
	this->_x = x;
	_objectRect->x = _x;
}

void Object::setY(int y){
	this->_y = y;
	_objectRect->y = _y;
}

void Object::setIsMovable(bool isMovable){
	this->_isMovable = isMovable;
}

void Object::setObjectTexture(SDL_Renderer* context){
	_objectTexture = IMG_LoadTexture(context, _texturePath.c_str());
}

void Object::setTexturePath(std::string newTexturePath){
	_texturePath = TEXTURE_PATH + newTexturePath;
}

SDL_Rect* Object::getSDLRect() const{
	return _objectRect;
}

std::string Object::getTexturePath() const{
	return _texturePath;
}

SDL_Texture* Object::getObjectTexture() const{
	return _objectTexture;
}

void Object::draw(SDL_Renderer* context){
	if (_objectTexture == nullptr)
		PrintErrors("No texture has been loaded. A texture must be set with the method: setObjectTexture.", SDL_GetError);
	if (SDL_RenderCopy(context, _objectTexture, NULL, _objectRect))
		PrintErrors("Failed to render " + _texturePath, SDL_GetError);
}

