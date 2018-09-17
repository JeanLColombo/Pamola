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
		terminals =
			from(terminals)
			>> where([](std::weak_ptr<CircuitTerminal> t) {return !t.expired(); })
			>> to_vector();
		
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

	eqMap CircuitNode::getEquations()
	{
		return { [this]()
			{
				std::complex<double> s{ 0.0 };

				for (auto t : getTerminals())
					s += t->getCurrent();

				return s;
			} 
		};
	}

	varMap CircuitNode::getVariables()
	{
		return { std::make_pair([this](std::complex<double> x) {setVoltage(x); },
				[this]() {return getVoltage(); }) };
	}

	const std::set<uint32_t> CircuitNode::getAdjacentComponents()
	{
		std::set<uint32_t> adjComponents;

		for (auto &terminal : getTerminals())
			adjComponents.insert(terminal->getId());

		return adjComponents;
	}

	Type CircuitNode::getPamolaType()
	{
		return Type::CircuitNode;
	}
}
