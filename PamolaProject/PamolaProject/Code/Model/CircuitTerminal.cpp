/**
 * Project PamolaCore
 */

#include "CircuitTerminal.h"

CircuitTerminal::CircuitTerminal()
{
}

CircuitTerminal::~CircuitTerminal()
{
}

CircuitElement * CircuitTerminal::getElement()
{
	return element;
}

CircuitNode * CircuitTerminal::getNode()
{
	return node;
}

CircuitNode * CircuitTerminal::connectTo(CircuitTerminal *)
{
	//TODO: Create the connectTo Circuit Terminal Body
	return nullptr;
}

CircuitNode * CircuitTerminal::connectTo(CircuitNode *)
{
	//TODO: Create the connectTo Node Body
	return nullptr;
}

std::complex<double> CircuitTerminal::getCurrent()
{
	return current;
}

std::complex<double> CircuitTerminal::getVoltage()
{
	if (!isConnected())
		return std::complex<double> NAN;

	return node->getVoltage();
}

bool CircuitTerminal::setCurrent(std::complex<double> value)
{
	current = value;
	return true;
}

bool CircuitTerminal::disconnect()
{
	//TODO: Create the disconnect fucntion's body
	return false;
}

bool CircuitTerminal::isConnected()
{
	return (node);
}

int CircuitTerminal::getDegreesOfFreedom()
{
	return 2;
}
