/**
 * Project PamolaCore
 */


#include "CircuitElement.h"
#include <vector>

/**
 * CircuitElement implementation
 */


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

/**
 * @return CircuitTerminal
 */
std::vector<CircuitTerminal*> CircuitElement::getTerminals() {
	return	terminals;
}

CircuitTerminal * CircuitElement::getTerminal(int localId)
{
	return terminals.at(localId);
}

/**
 * @param terminal
 */
