#ifndef _OBJECTPHYSICALPROPERTIESSERVICE_H
#define _OBJECTPHYSICALPROPERTIESSERVICE_H

#include "ObjectBodies.h"
#include "ObjectPhysicalProperties.h"
#include "Position.h"
#include "ConversionService.h"

namespace ObjectPhysicalPropertiesService {
	ObjectPhysicalProperties::ObjectPhysicalProperties objectPhysicalProperties(const ObjectBodies &objectBody);
	ObjectPhysicalProperties::ObjectPhysicalProperties objectPhysicalProperties(const ObjectBodies &objectBody, const Position &position);
}
#endif