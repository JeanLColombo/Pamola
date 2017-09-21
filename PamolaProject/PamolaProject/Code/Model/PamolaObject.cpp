/**
 * Project PamolaCore
 */


#include "PamolaObject.h"
#include <unordered_map>

/**
 * PamolaObject implementation
 */

PamolaObject::PamolaObject() {
	id = guid++;
	pamolaInstances.insert({id,this});
}

PamolaObject::~PamolaObject()
{
	pamolaInstances.erase(getId());
}

/**
 * @return unsign int
 */
uint32_t PamolaObject::getId() {
    return id;
}


/**
 * @return object
 */

PamolaObject * PamolaObject::getPamolaInstance(uint32_t id)
{
	return pamolaInstances.at(id);
}

 int PamolaObject::getDegreesOfFreedom()
 {
 }

