/**
 * Project PamolaCore
 */

 //TODO Organize this code

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

void PamolaObject::clear()
{
	BOOST_FOREACH(auto pamObject, pamolaInstances)
	{
		delete pamObject.second;
	}
	pamolaInstances.clear();
}

 int PamolaObject::getDegreesOfFreedom()
 {
 }
