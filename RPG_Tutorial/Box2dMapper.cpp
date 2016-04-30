#include "Box2dMapper.h"


b2FixtureDef mapToFixture(const ObjectPhysicalProperties &props) {
	b2FixtureDef fixtureDef;
	fixtureDef.density = props.density;
	fixtureDef.friction = props.friction;
	return fixtureDef;
}


b2BodyDef mapToBody(const ObjectPhysicalProperties &props) {
	b2BodyDef bodyDef;
	bodyDef.type = props.bodyType;
	bodyDef.position.Set(props.x, props.y);
	return bodyDef;
}


b2PolygonShape mapToShape(const ObjectPhysicalProperties &props) {
	b2PolygonShape box;
	box.SetAsBox(props.halfWidth, props.halfHeight);
	return box;
}
