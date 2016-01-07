#pragma once
/*
The entire point of this class is to create instances of objects. This class will ensure that the background is the first instance
that is input into the levelobjects pointer vector and will handle all the caching.
*/
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
};

