#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

using std::string;

/*
An enum containing all objects in the game.
*/
enum Character: int{
	BEGINNING,
	NONE,
	JIM,
	FLYING_HEART_SMALL,
	FLYING_HEART_LARGE,
	BACKGROUND,
	LIGHT_GRAY_PLATFORM,
	LIGHT_GREEN_PLATFORM,
	END
};
#endif