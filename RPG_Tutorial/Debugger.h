#ifndef _DEBUGGER_H
#define _DEBUGGER_H

#include "SDL2.0\SDL.h"
#include <Box2D\Box2D.h>
#include "ConversionService.h"
#include "Box2dService.h"

class Debugger {
public:
	void setContext(SDL_Renderer* context);

	void renderAllFixturesOnBody(const b2Body& objectBody) const;
	void renderFixture(const b2Body& objectBody, const b2Fixture& fixture) const;
	void renderRectangle(const SDL_Rect &rectangle);

private:
	SDL_Renderer* context;
};
#endif