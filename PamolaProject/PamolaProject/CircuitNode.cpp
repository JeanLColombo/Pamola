/**
 * Project PamolaCore
 */

#include "stdafx.h"
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

std::vector<PamolaObject*> CircuitNode::getAdjacentComponents()
{
	using namespace cpplinq;
	auto result =
		from(terminals)
		>> select([](CircuitTerminal* c) {return static_cast<PamolaObject*>(c); })
		>> to_vector;

	return result;
}

PamolaType CircuitNode::getPamolaType()
{
	return PamolaType::CircuitNode;
}

int CircuitNode::getDegreesOfFreedom()
{
	return (-static_cast<int>(terminals.size()));
}
