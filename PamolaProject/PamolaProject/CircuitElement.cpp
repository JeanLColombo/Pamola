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
		for (uint32_t i = 0; i < numberOfTerminals; i++)
		{
			//std::shared_ptr<CircuitTerminal> terminalInstance{ new CircuitTerminal(this) };
			//auto terminalInstance = std::make_shared<CircuitTerminal>(this);
			terminals.push_back(CircuitTerminal(this));
		}			
		
		return true;
	}	
	return false;
}

//const std::vector<std::shared_ptr<CircuitTerminal>> CircuitElement::getTerminals()
const std::vector<CircuitTerminal &> CircuitElement::getTerminals()
{
	return terminals;
}

//const std::shared_ptr<CircuitTerminal> CircuitElement::getTerminal(uint32_t localId)
CircuitTerminal & CircuitElement::getTerminal(uint32_t localId)
{
	return terminals.at(localId);
}

const std::vector<std::shared_ptr<PamolaObject>> CircuitElement::getAdjacentComponents()
{
	using namespace cpplinq;
	auto result =
		from(terminals)
		>> select([](CircuitTerminal &t) {return static_cast<std::shared_ptr<PamolaObject>>(t.shared_from_this()); })
		>> to_vector();
	
	auto x1 = shared_from_this();

	return result;
}

PamolaType CircuitElement::getPamolaType()
{
	return PamolaType::CircuitElement;
}
