#include "stdafx.h"
#include "PamolaObject.h"
#include "PamolaEngine.h"

namespace Pamola
{
	Object::Object()
	{
	}

	Object::~Object()
	{
	}

	const std::set<uint32_t> & Object::getConnectedComponents()
	{
		std::set<uint32_t> componentList{ getId() };

		for (auto elementId : getAdjacentComponents())
			componentList = getEngine()->getLocalObject(elementId)->getConnectedComponents(componentList);

		return componentList;
	}

	std::set<uint32_t> & Object::getConnectedComponents(std::set<uint32_t> &componentList)
	{
		if (componentList.find(getId()) != componentList.end())
			return componentList;
		
		componentList.insert(getId());

		for (auto elementId : getAdjacentComponents())
			componentList = getEngine()->getLocalObject(elementId)->getConnectedComponents(componentList);

		return componentList;
	}

	std::shared_ptr<Circuit> Object::getCircuit()
	{
		using namespace cpplinq;
		auto circuitList =
			from(getConnectedComponents())
			>> select([this](uint32_t i) {return getEngine()->getLocalObject(i); })
			>> to_vector();
		
		return getEngine()->createCircuit(circuitList);
	}

	const std::shared_ptr<Engine> Object::getEngine()
	{
		return engine.lock();
	}
	
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