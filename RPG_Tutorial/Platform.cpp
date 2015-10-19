#include "Platform.h"


Platform::Platform() : Object(){
	_isPlatform = true;
}

Platform::Platform(int x, int y, int width, int height) : Object(x, y, width, height){
	_isPlatform = true;
}

Platform::Platform(const Platform &platform): Object(platform){
	_isPlatform = true;
}

Platform::~Platform(){
}


Platform& Platform::operator=(Platform &platform){
	Object::operator=(platform);
	return *this;
}
