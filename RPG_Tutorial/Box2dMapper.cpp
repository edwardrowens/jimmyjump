#include "Box2dMapper.h"


b2FixtureDef Box2dMapper::mapToFixture(const ObjectPhysicalProperties::ObjectPhysicalProperties &props) {
	b2FixtureDef fixtureDef;
	fixtureDef.density = props.density;
	fixtureDef.friction = props.friction;
	return fixtureDef;
}


b2BodyDef Box2dMapper::mapToBody(const ObjectPhysicalProperties::ObjectPhysicalProperties &props) {
	b2BodyDef bodyDef;
	bodyDef.type = props.bodyType;
	bodyDef.position.Set(props.x, props.y);
	return bodyDef;
}


b2PolygonShape Box2dMapper::mapToShape(const ObjectPhysicalProperties::ObjectPhysicalProperties &props) {
	b2PolygonShape box;
	box.SetAsBox(props.w, props.h);
	return box;
}
