/**
 * Project PamolaCore
 */

#include "stdafx.h"
#include "PamolaObject.h"

std::unordered_map<uint32_t, PamolaObject *> PamolaObject::pamolaInstances = {};
uint32_t PamolaObject::guid = 0;

PamolaObject::PamolaObject() {
	id = guid++;
	pamolaInstances.insert({id,this});
}

PamolaObject::~PamolaObject()
{
	pamolaInstances.erase(getId());
}

PamolaObject * PamolaObject::getPamolaInstance(uint32_t id)
{
	return pamolaInstances.at(id);
}

void PamolaObject::clear()
{
	for each (auto pamObject in pamolaInstances)
	{
		delete pamObject.second;
	}
	pamolaInstances.clear();
}


uint32_t PamolaObject::getId() {
	return id;
}