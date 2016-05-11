#ifndef _WORLDCONSTANTS_H
#define _WORLDCONSTANTS_H

#include <Box2D\Box2D.h>

namespace WorldConstants {
	const b2Vec2 DEFAULT_GRAVITY(0.0f, -9.8f);
	const int32 VELOCITY_ITERATIONS = 8;
	const int32 POSITION_ITERATIONS = 3;
	const float32 UPDATE_TICK = 1.0f / 60.0f;
	const float32 UPDATE_TICK_IN_SECONDS = UPDATE_TICK * 1000;
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const int PIXELS_PER_METER = 20; // how many pixels per meter
	const float X_ORIGIN = WINDOW_WIDTH / 2;
	const float Y_ORIGIN = WINDOW_HEIGHT / 2;
}
#endif