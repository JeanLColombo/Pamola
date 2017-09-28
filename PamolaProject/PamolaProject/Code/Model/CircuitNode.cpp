/**
 * Project PamolaCore
 */

#include "CircuitNode.h"

CircuitNode::CircuitNode()
{
}

CircuitNode::~CircuitNode()
{
}

CircuitNode * CircuitNode::connectTo(CircuitNode *node)
{
	if (this == node)
		return this;
	
	std::vector<CircuitTerminal*> addedTerminals = node->getTerminals();

	for each (CircuitTerminal* terminal in addedTerminals)
	{
		terminal->disconnect();
		terminal->connectTo(this);
	}

	return this;
}

std::vector<CircuitTerminal*> CircuitNode::getTerminals()
{
	return terminals;
}

std::complex<double> CircuitNode::getVoltage()
{
	return voltage;
}

bool CircuitNode::setVoltage(std::complex<double> value)
{
	voltage = value;
	return true;
}

int CircuitNode::getDegreesOfFreedom()
{
	return (-terminals.size());
}
