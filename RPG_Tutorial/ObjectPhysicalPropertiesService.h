#ifndef _OBJECTPHYSICALPROPERTIESSERVICE_H
#define _OBJECTPHYSICALPROPERTIESSERVICE_H

#include "ObjectBodies.h"
#include "ObjectPhysicalProperties.h"

namespace ObjectPhysicalPropertiesService {
	ObjectPhysicalProperties::ObjectPhysicalProperties objectPhysicalProperties(const ObjectBodies::ObjectBodies &objectBody);
}
#endif