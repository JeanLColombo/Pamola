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
	for each (CircuitTerminal* terminal in getTerminals())
	{
		delete terminal;
	}
}

bool CircuitElement::createTerminals(uint32_t numberOfTerminals)
{
	//TODO: Check this line
	//if (terminals.empty && (numberOfTerminals > 0))
	if (numberOfTerminals > 0)
	{
		
		for (uint32_t i = 0; i < numberOfTerminals; i++)
		{
			terminals.push_back(new CircuitTerminal());
		}

		return true;
	}	
	return false;
}


std::vector<CircuitTerminal*> CircuitElement::getTerminals() {
	return	terminals;
}

CircuitTerminal * CircuitElement::getTerminal(uint32_t localId)
{
	return terminals.at(localId);
}

std::vector<PamolaObject*> CircuitElement::getAdjacentComponents()
{
	using namespace cpplinq;
	auto result =
		from(terminals)
		>> select([](CircuitTerminal* c) {return static_cast<PamolaObject*>(c); })
		>> to_vector;

	return result;
}

PamolaType CircuitElement::getPamolaType()
{
	return PamolaType::CircuitElement;
}
