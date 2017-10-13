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

const std::unordered_map<uint32_t, PamolaObject*> PamolaObject::getPamolaInstances()
{
	return pamolaInstances;
}

PamolaObject * PamolaObject::getPamolaInstance(uint32_t id)
{
	return pamolaInstances.at(id);
}

void PamolaObject::clear()
{
	for each (std::pair<const uint32_t,PamolaObject*> pamObject in pamolaInstances)
	{
		PamolaObject *temporaryPamola = pamObject.second;
		delete temporaryPamola;
	}
	pamolaInstances.clear();
}


uint32_t PamolaObject::getId() {
	return id;
}