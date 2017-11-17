/**
 * Project PamolaCore
 */

#include "stdafx.h"
#include "CircuitElement.h"

CircuitElement::CircuitElement()
{
}

CircuitElement::~CircuitElement()
{
}

bool CircuitElement::createTerminals(uint32_t numberOfTerminals)
{
	if (numberOfTerminals > 0)
	{
		//TODO: Check if the terminals were created.
		//for (uint32_t i = 0; i < numberOfTerminals; i++)
			//terminals.push_back(std::make_shared<CircuitTerminal>());

		return true;
	}	
	return false;
}

const std::vector<std::shared_ptr<CircuitTerminal>> CircuitElement::getTerminals()
{
	return	terminals;
}

const std::shared_ptr<CircuitTerminal> CircuitElement::getTerminal(uint32_t localId)
{
	return terminals.at(localId);
}

const std::vector<std::shared_ptr<PamolaObject>> CircuitElement::getAdjacentComponents()
{
	using namespace cpplinq;
	auto result =
		from(terminals)
		>> select([](std::shared_ptr<CircuitTerminal> c) {return static_cast<std::shared_ptr<PamolaObject>>(c); })
		>> to_vector();

	return result;
}

PamolaType CircuitElement::getPamolaType()
{
	return PamolaType::CircuitElement;
}
