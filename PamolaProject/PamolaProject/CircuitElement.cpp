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
