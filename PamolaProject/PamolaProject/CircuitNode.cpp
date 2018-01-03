#include "stdafx.h"
#include "CircuitNode.h"
#include "CircuitTerminal.h"

namespace Pamola
{
	CircuitNode::CircuitNode()
	{
	}

	CircuitNode::~CircuitNode()
	{
	}

	std::shared_ptr<CircuitNode> CircuitNode::connectTo(std::shared_ptr<CircuitNode> node)
	{
		if (shared_from_this() == node)
			return node;

		const std::vector<std::shared_ptr<CircuitTerminal>> addedTerminals = node->getTerminals();

		for (auto terminal : addedTerminals)
		{
			terminal->disconnect();
			terminal->connectTo(shared_from_this());
		}

		return shared_from_this();
	}

	const std::vector<std::shared_ptr<CircuitTerminal>> CircuitNode::getTerminals()
	{
		using namespace cpplinq;
		auto result =
			from(terminals)
			>> select([](std::weak_ptr<CircuitTerminal> t) {return t.lock(); })
			>> to_vector();

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

	const std::vector<std::shared_ptr<Object>> CircuitNode::getAdjacentComponents()
	{
		using namespace cpplinq;
		auto result =
			from(terminals)
			>> select([](std::weak_ptr<CircuitTerminal> t) {return static_cast<std::shared_ptr<Object>>(t.lock()); })
			>> to_vector();

		return result;
	}

	Type CircuitNode::getPamolaType()
	{
		return Type::CircuitNode;
	}

	int CircuitNode::getDegreesOfFreedom()
	{
		return (-static_cast<int>(terminals.size()));
	}
}
