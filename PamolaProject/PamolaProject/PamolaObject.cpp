/**
 * Project PamolaCore
 */

#include "stdafx.h"
#include "PamolaObject.h"

std::unordered_map<uint32_t, PamolaObject*> PamolaObject::pamolaInstances = {};
uint32_t PamolaObject::guid = 0;

PamolaObject::PamolaObject() {
	id = guid++;
	pamolaInstances.insert({ id,this });
}

PamolaObject::~PamolaObject()
{
	pamolaInstances.erase(getId());
}

std::set<uint32_t> PamolaObject::getConnectedComponents()
{
	//TODO: But how?

	std::set<uint32_t> componentList{ id };
	
	for (auto component : getAdjacentComponents())
	{
		if (componentList.find(component->getId()) != componentList.end())
		{

		}
		componentList.insert(component->getId());
	}


	return std::set<uint32_t>();
}

std::set<uint32_t> PamolaObject::getConnectedComponents(std::set<uint32_t>)
{
	return std::set<uint32_t>();
}

const std::unordered_map<uint32_t, PamolaObject*> & PamolaObject::getPamolaInstances()
{
	return pamolaInstances;
}

PamolaObject* PamolaObject::getPamolaInstance(uint32_t id)
{
	return getPamolaInstances().at(id);
}

//std::shared_ptr<Circuit> PamolaObject::getCircuit()
//{
//	//TODO: Check if it is going to remain a shared_ptr
//
//	//TODO: std::vector of components
//	
//	//TODO: Instantiate a new circuit object with std::vector of components
//
//	//TODO: Return pointer to circuit object
//	return nullptr;
//}

uint32_t PamolaObject::getId() {
	return id;
}

PamolaType PamolaObject::getPamolaType()
{
	return PamolaType::Other;
}
