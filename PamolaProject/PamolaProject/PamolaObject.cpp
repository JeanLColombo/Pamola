/**
 * Project PamolaCore
 */

#ifndef __GNUC__
#include "stdafx.h"
#endif
#include "cpplinq.hpp"
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

std::vector<PamolaObject*> PamolaObject::getCircuitElements()
{
	auto result =
		cpplinq::from(getPamolaInstances())
		>> cpplinq::where([](std::pair<uint32_t, PamolaObject*> const & kv) {return kv.second->getPamolaType() == PamolaType::CircuitElement; })
		>> cpplinq::select([](std::pair<uint32_t, PamolaObject*> const & kv) {return kv.second; })
		>> cpplinq::to_vector()
		;

	return result;
}

PamolaObject * PamolaObject::getPamolaInstance(uint32_t id)
{
	return pamolaInstances.at(id);
}

void PamolaObject::clear()
{
#ifdef __GNUC__
	for (auto element : PamolaObject::getCircuitElements())
#else
	for each (auto element in PamolaObject::getCircuitElements())
#endif
	{
		delete element;
	}
}


uint32_t PamolaObject::getId() {
	return id;
}

PamolaType PamolaObject::getPamolaType()
{
	return PamolaType::Other;
}
