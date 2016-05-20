#ifndef _BOX2DDEBUGGER_H
#define _BOX2DDEBUGGER_H

#include "SDL2.0\SDL.h"
#include <Box2D\Box2D.h>
#include "CoordinateService.h"
#include "Box2dService.h"

class Box2dDebugger {
public:
	void setContext(SDL_Renderer* context);

	void renderAllFixturesOnBody(const b2Body& objectBody) const;
	void renderFixture(const b2Body& objectBody, const b2Fixture& fixture) const;

private:
	SDL_Renderer* context;
};
#endif