#ifndef _COLLISIONCATEGORY_H
#define _COLLISIONCATEGORY_H

#include "CharacterInformation.h"
#include <Box2D\Common\b2Math.h>
#include "CharacterGroupingService.h"

namespace CollisionCategory {
	enum CollisionCategory {
		// I collide with nothing.
		NONE = 0x0001,

		// I collide with everything
		EVERYTHING = 0x0002,

		// I am an enemy
		ENEMY = 0x0004,

		// I am a friendly
		FRIENDLY = 0x0008
	};
}

namespace CollisionCategoryService {
	uint16 retrieveCategoryBits(const Character &character);
	uint16 retrieveMaskBits(const Character &character);
};

CollisionCategory::CollisionCategory retrieveCollisionCategory(const CharacterGroup &characterGroup);

#endif