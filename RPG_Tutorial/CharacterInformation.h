#pragma once

// Contains the information which pertains to all associated characters within the game.
// BEGINNING and END need to be at the beginning and end respectively (for iteration).
enum Character : int{
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

enum CharacterGroup : int{
	OBJECT,
	MAIN_CHARACTER,
	PLATFORM,
	MOVABLE_OBJECT
};