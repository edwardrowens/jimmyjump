#include "CollisionCategory.h"

uint16 CollisionCategoryService::retrieveCategoryBits(const Character &character) {
	uint16 categoryBits = CollisionCategory::NONE;
	CharacterGroup characterGroup = CharacterGroupingService::retrieveCharacterGrouping(character);

	switch (characterGroup) {
	case CharacterGroup::MAIN_CHARACTER:
		categoryBits = CollisionCategory::FRIENDLY;
		break;
	case CharacterGroup::MOVABLE_OBJECT:
		categoryBits = CollisionCategory::ENEMY;
		break;
	case CharacterGroup::OBJECT:
		if (character == Character::BACKGROUND)
			categoryBits = CollisionCategory::NONE;
		else
			categoryBits = CollisionCategory::EVERYTHING;
		break;
	case CharacterGroup::PLATFORM:
		categoryBits = CollisionCategory::EVERYTHING;
		break;
	}

	return categoryBits;
}


uint16 CollisionCategoryService::retrieveMaskBits(const Character &character) {
	// by default, everything is masked (you don't collide with anything)
	uint16 maskBits = 0x0000;
	uint16 collisionCategory = CollisionCategoryService::retrieveCategoryBits(character);

	switch (collisionCategory) {
	case CollisionCategory::FRIENDLY:
		maskBits = CollisionCategory::FRIENDLY | CollisionCategory::EVERYTHING;
		break;
	case CollisionCategory::ENEMY:
		maskBits = CollisionCategory::FRIENDLY | CollisionCategory::EVERYTHING;
		break;
	case CollisionCategory::EVERYTHING:
		maskBits = CollisionCategory::FRIENDLY | CollisionCategory::EVERYTHING | CollisionCategory::ENEMY;
		break;
	}

	return maskBits;
}