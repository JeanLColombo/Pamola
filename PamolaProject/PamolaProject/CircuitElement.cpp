/**
 * Project PamolaCore
 */

#ifndef __GNUC__
#include "stdafx.h"
#endif
#include "CircuitElement.h"

CircuitElement::CircuitElement()
{
}

CircuitElement::~CircuitElement()
{
#ifdef __GNUC__
	for(CircuitTerminal* terminal: getTerminals())
#else
	for each (CircuitTerminal* terminal in getTerminals())
#endif
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

PamolaType CircuitElement::getPamolaType()
{
	return PamolaType::CircuitElement;
}
