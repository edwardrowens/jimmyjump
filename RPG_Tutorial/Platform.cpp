#include "Platform.h"


Platform::Platform() : Object(){
	isPlatform = true;
}

Platform::Platform(int x, int y, int width, int height) : Object(x, y, width, height){
	isPlatform = true;
}

Platform::Platform(const Platform &platform): Object(platform){
	isPlatform = true;
}

Platform::~Platform(){
}


Platform& Platform::operator=(Platform &platform){
	Object::operator=(platform);
	return *this;
}
