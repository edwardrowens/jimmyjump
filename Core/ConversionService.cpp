#include "ConversionService.h"

b2Vec2 ConversionService::screenPointToWorldPoint(const int &x, const int &y) {
	return b2Vec2((x - WorldConstants::X_ORIGIN) / WorldConstants::PIXELS_PER_METER, (WorldConstants::Y_ORIGIN - y) / WorldConstants::PIXELS_PER_METER);
}


b2Vec2 ConversionService::worldPointToScreenPoint(const float32 &x, const float32 &y) {
	return b2Vec2((WorldConstants::X_ORIGIN + (x * WorldConstants::PIXELS_PER_METER)), WorldConstants::Y_ORIGIN - (y * WorldConstants::PIXELS_PER_METER));
}


b2Vec2 ConversionService::screenPointToWorldPoint(const b2Vec2 &point) {
	return screenPointToWorldPoint(point.x, point.y);
}


b2Vec2 ConversionService::worldPointToScreenPoint(const b2Vec2 &point) {
	return worldPointToScreenPoint(point.x, point.y);
}


float32 ConversionService::screenValueToWorldValue(const int &value) {
	return (float) value / WorldConstants::PIXELS_PER_METER;
}


int ConversionService::worldValueToScreenValue(const float32 &value) {
	return value * WorldConstants::PIXELS_PER_METER;
}


b2Vec2 ConversionService::retrieveRenderingRectangleForNonSensorFixture(const b2Body &objectBody, const int &width, const int &height) {
	b2Vec2 currentPosition = Box2dService::retrieveTopLeftVertex(objectBody);
	b2Vec2 anotherPosition = Box2dService::retrieveBottomRightVertex(objectBody);

	float32 imageCenterX = (currentPosition.x + anotherPosition.x) / 2;
	float32 imageCenterY = (currentPosition.y + anotherPosition.y) / 2;

	return ConversionService::worldPointToScreenPoint(imageCenterX - (ConversionService::screenValueToWorldValue(width) / 2), imageCenterY + (ConversionService::screenValueToWorldValue(height) / 2));
}