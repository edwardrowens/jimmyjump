#include "Platform.h"


Platform::Platform() : Object(){
	isPlatform = true;
}

Platform::Platform(Position position) : Object(position){
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
