#ifndef _BOX2DDEBUGGER_H
#define _BOX2DDEBUGGER_H

#include <Box2D\Debug\DebugDraw.h>
#include "SDL2.0\SDL.h"

class Box2dDebugger : public DebugDraw {
public:
	Box2dDebugger();
	~Box2dDebugger();

	void setContext(SDL_Renderer* context);
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color); 
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color); 
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color); 
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color); 
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color); 
	void DrawTransform(const b2Transform& xf);

private:
	SDL_Renderer* context;
};
#endif