#ifndef _OBJECTPHYSICALPROPERTIESSERVICE_H
#define _OBJECTPHYSICALPROPERTIESSERVICE_H

#include "ObjectBodies.h"
#include "ObjectPhysicalProperties.h"
#include "Position.h"
#include "CoordinateService.h"

namespace ObjectPhysicalPropertiesService {
	ObjectPhysicalProperties::ObjectPhysicalProperties objectPhysicalProperties(const ObjectBodies::ObjectBodies &objectBody);
	ObjectPhysicalProperties::ObjectPhysicalProperties objectPhysicalProperties(const ObjectBodies::ObjectBodies &objectBody, const Position &position);
}
#endif