#include "Platform.h"


Platform::Platform() : Object(){
}

Platform::Platform(int x, int y, int width, int height) : Object(x, y, width, height){
}

Platform::~Platform(){
}

Platform::Platform(const Platform &platform): Object(platform){
}

Platform& Platform::operator=(Platform &platform){
	Object::operator=(platform);
	return *this;
}
