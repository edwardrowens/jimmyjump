#include "Platform.h"


Platform::Platform(b2Body* objectBody, Character character) : Object(objectBody, character){
	group = CharacterGroup::PLATFORM;
	objectBody->SetFixedRotation(false);
}

Platform::Platform(const Platform &platform): Object(platform){
}

Platform::~Platform(){
}


Platform& Platform::operator=(Platform &platform){
	Object::operator=(platform);
	return *this;
}
