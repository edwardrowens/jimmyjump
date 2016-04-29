#include "Platform.h"


Platform::Platform() : Object(){
	isPlatform = true;
}

Platform::Platform(b2Body* objectBody, Character character) : Object(objectBody, character){
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
