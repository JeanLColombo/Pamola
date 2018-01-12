#include "stdafx.h"
#include "PamolaObject.h"

namespace Pamola
{
	Object::Object()
	{
	}

	Object::~Object()
	{
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

	const std::shared_ptr<Engine> Object::getEngine()
	{
		return engine.lock();
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

	uint32_t Object::getId() const
	{
		return id;
	}

	bool Object::operator<(const Pamola::Object &o)
	{
		return getId() < o.getId();
	}

	bool Object::operator>(const Pamola::Object &o)
	{
		return getId() > o.getId();
	}

	bool Object::operator<=(const Pamola::Object &o)
	{
		return getId() <= o.getId();
	}

	bool Object::operator>=(const Pamola::Object &o)
	{
		return getId() >= o.getId();
	}

	bool Object::operator==(const Pamola::Object &o)
	{
		return getId() == o.getId();
	}

	bool Object::operator!=(const Pamola::Object &o)
	{
		return getId() != o.getId();
	}

	Type Object::getPamolaType()
	{
		return Type::Other;
	}

	bool operator<(const std::shared_ptr<Object> o1, const std::shared_ptr<Object> o2)
	{
		return *o1 < *o2;
	}

	bool operator>(const std::shared_ptr<Object> o1, const std::shared_ptr<Object> o2)
	{
		return *o1 > *o2;
	}

	bool operator<=(const std::shared_ptr<Object> o1, const std::shared_ptr<Object> o2)
	{
		return *o1 <= *o2;
	}

	bool operator>=(const std::shared_ptr<Object> o1, const std::shared_ptr<Object> o2)
	{
		return *o1 >= *o2;
	}

	bool operator==(const std::shared_ptr<Object> o1, const std::shared_ptr<Object> o2)
	{
		return *o1 == *o2;
	}

	bool operator!=(const std::shared_ptr<Object> o1, const std::shared_ptr<Object> o2)
	{
		return *o1 != *o2;
	}

}