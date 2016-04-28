#pragma once
#include <Box2D\Box2D.h>

namespace WorldConstants {
	const b2Vec2 DEFAULT_GRAVITY(0.0f, -10.0f);
	const int32 VELOCITY_ITERATIONS = 8;
	const int32 POSITION_ITERATIONS = 3;
	const float32 UPDATE_TICK = 1.0f / 60.0f;
	const int WINDOW_WIDTH = 768;
	const int WINDOW_HEIGHT = 600;
}
