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

CircuitNode & CircuitNode::connectTo(CircuitNode &node)
{
	if (this == &node)
		return node;
	
	const std::vector<std::shared_ptr<CircuitTerminal>> addedTerminals = node.getTerminals();

	for each (auto terminal in addedTerminals)
	{
		terminal->disconnect();
		terminal->connectTo(*this);
	}

	return *this;
}

const std::vector<std::shared_ptr<CircuitTerminal>> CircuitNode::getTerminals()
{
	using namespace cpplinq;
	auto result =
		from(terminals)
		>> select([](std::weak_ptr<CircuitTerminal> t) {return t.lock(); })
		>> to_vector;

	return result;
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

const std::vector<std::shared_ptr<PamolaObject>> CircuitNode::getAdjacentComponents()
{
	using namespace cpplinq;
	auto result =
		from(terminals)
		>> select([](std::weak_ptr<CircuitTerminal> t) {return std::make_shared<PamolaObject>(t); })
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
