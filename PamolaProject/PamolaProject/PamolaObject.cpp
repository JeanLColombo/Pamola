#include "stdafx.h"
#include "cpplinq.hpp"
#include "PamolaObject.h"

namespace Pamola
{
	uint32_t Object::guid = 0;

	Object::Object()
	{
		id = guid++;
		Engine::getLocalEngine()->localObjects.insert(this);
	}

	Object::~Object()
	{
		Engine::getLocalEngine()->localObjects.erase(this);
	}

	std::set<uint32_t> Object::getConnectedComponents()
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

	std::set<uint32_t> Object::getConnectedComponents(std::set<uint32_t>)
	{
		return std::set<uint32_t>();
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

	uint32_t Object::getId() {
		return id;
	}

	Type Object::getPamolaType()
	{
		return Type::Other;
	}
}