#include "CharacterGroupingService.h"

namespace CharacterGroupingService {
	CharacterGroup retrieveCharacterGrouping(const Character& character) {
		switch (character) {
		case Character::NONE:
			return CharacterGroup::OBJECT;
			break;
		case Character::BACKGROUND:
			return CharacterGroup::OBJECT;
			break;
		case Character::FLYING_HEART_LARGE:
			return CharacterGroup::MOVABLE_OBJECT;
			break;
		case Character::FLYING_HEART_SMALL:
			return CharacterGroup::MOVABLE_OBJECT;
			break;
		case Character::JIM:
			return CharacterGroup::MAIN_CHARACTER;
			break;
		case Character::LIGHT_GRAY_PLATFORM:
			return CharacterGroup::PLATFORM;
			break;
		case Character::LIGHT_GREEN_PLATFORM:
			return CharacterGroup::PLATFORM;
			break;
		}
	}
}
