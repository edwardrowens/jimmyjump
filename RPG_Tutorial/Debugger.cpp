#include "Debugger.h"


void Debugger::setContext(SDL_Renderer* context) {
	this->context = context;
}


void Debugger::renderAllFixturesOnBody(const b2Body& objectBody) const {
	for (const b2Fixture* f = objectBody.GetFixtureList(); f; f = f->GetNext()) {
		Debugger::renderFixture(objectBody, *f);
	}
}


void Debugger::renderFixture(const b2Body& objectBody, const b2Fixture& fixture) const {
	b2Vec2 topLeftVertexWorld = Box2dService::retrieveTopLeftVertex(objectBody, fixture);
	b2Vec2 topRightVertexWorld = Box2dService::retrieveTopRightVertex(objectBody, fixture);
	b2Vec2 bottomRightVertexWorld = Box2dService::retrieveBottomRightVertex(objectBody, fixture);
	b2Vec2 bottomLeftVertexWorld = Box2dService::retrieveBottomLeftVertex(objectBody, fixture);

	b2Vec2 topLeftVertexScreen = ConversionService::worldPointToScreenPoint(topLeftVertexWorld);
	b2Vec2 topRightVertexScreen = ConversionService::worldPointToScreenPoint(topRightVertexWorld);
	b2Vec2 bottomRightVertexScreen = ConversionService::worldPointToScreenPoint(bottomRightVertexWorld);
	b2Vec2 bottomLeftVertexScreen = ConversionService::worldPointToScreenPoint(bottomLeftVertexWorld);

	SDL_SetRenderDrawColor(context, 255, 0, 0, 255);
	SDL_RenderDrawLine(context, topLeftVertexScreen.x, topLeftVertexScreen.y, topRightVertexScreen.x, topRightVertexScreen.y); // 1 - 2
	SDL_RenderDrawLine(context, topLeftVertexScreen.x, topLeftVertexScreen.y, bottomLeftVertexScreen.x, bottomLeftVertexScreen.y); // 1 - 3
	SDL_RenderDrawLine(context, bottomLeftVertexScreen.x, bottomLeftVertexScreen.y, bottomRightVertexScreen.x, bottomRightVertexScreen.y); // 3 - 4
	SDL_RenderDrawLine(context, bottomRightVertexScreen.x, bottomRightVertexScreen.y, topRightVertexScreen.x, topRightVertexScreen.y); // 4 - 2
}


void Debugger::renderRectangle(const SDL_Rect &rectangle) {
	SDL_SetRenderDrawColor(context, 0, 255, 0, 255);
	SDL_RenderDrawRect(context, &rectangle);
}
	//TTF_Font* Sans = TTF_OpenFont("Resources/Fonts/ARLRDBD.ttf", 24); //this opens a font style and sets a size
	//SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	//SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, std::string("(" + std::to_string(objectRect.x) + ", " + std::to_string(objectRect.y) + ")").c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	//SDL_Texture* Message = SDL_CreateTextureFromSurface(context, surfaceMessage); //now you can convert it into a texture

	//if (getIsMovable()) {
	//	SDL_Rect Message_rect; //create a rect
	//	Message_rect.x = objectRect.x - 50;  //controls the rect's x coordinate 
	//	Message_rect.y = objectRect.y - 20; // controls the rect's y coordinte
	//	Message_rect.w = 50; // controls the width of the rect
	//	Message_rect.h = 20; // controls the height of the rect
	//	SDL_RenderCopy(context, Message, NULL, &Message_rect);
	//}