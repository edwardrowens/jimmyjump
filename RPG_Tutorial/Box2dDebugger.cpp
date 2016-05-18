#include "Box2dDebugger.h"


void Box2dDebugger::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
	SDL_Rect rect;
	rect.x = vertices[0].x;
	rect.y = vertices[0].y;
	rect.w = (vertices[0].x - vertices[1].x) > 0 ? vertices[0].x - vertices[1].x : vertices[1].x - vertices[0].x;
	rect.h = (vertices[0].y - vertices[1].y) > 0 ? vertices[0].y - vertices[1].y : vertices[1].y - vertices[0].y;

	int success = SDL_RenderDrawRect(context, &rect);
}


void Box2dDebugger::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
	SDL_Rect rect;
	rect.x = vertices[0].x;
	rect.y = vertices[0].y;
	rect.w = (vertices[0].x - vertices[1].x) > 0 ? vertices[0].x - vertices[1].x : vertices[1].x - vertices[0].x;
	rect.h = (vertices[0].y - vertices[1].y) > 0 ? vertices[0].y - vertices[1].y : vertices[1].y - vertices[0].y;

	b2Vec2 first = CoordinateService::worldToScreen(vertices[0].x, vertices[0].y);
	b2Vec2 second = CoordinateService::worldToScreen(vertices[1].x, vertices[1].y);
	std::cout << "called\n";
	//SDL_RenderClear(context);
	SDL_SetRenderDrawColor(context, 255, 0, 0, 255);
	SDL_RenderDrawLine(context, 100, 200, 500, 500);
	SDL_RenderPresent(context);
}


void Box2dDebugger::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {

}


void Box2dDebugger::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {

}


void Box2dDebugger::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {

}


void Box2dDebugger::DrawTransform(const b2Transform& xf) {

}


void Box2dDebugger::setContext(SDL_Renderer* context) {
	this->context = context;
}