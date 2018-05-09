#include "stdafx.h"
#include "CircuitElement.h"
#include "CircuitTerminal.h"

namespace Pamola
{
	CircuitElement::CircuitElement(uint32_t numberOfTerminals)
		: numberOfterminals(numberOfTerminals)
	{
	}

	CircuitElement::~CircuitElement()
	{
	}

	const std::vector<std::shared_ptr<CircuitTerminal>> CircuitElement::getTerminals()
	{
		return terminals;
	}

	const std::shared_ptr<CircuitTerminal> CircuitElement::getTerminal(uint32_t localId)
	{
		return terminals.at(localId);
	}

	const std::set<uint32_t> CircuitElement::getAdjacentComponents()
	{
		std::set<uint32_t> adjComponents;

		for (auto &terminal : getTerminals())
			adjComponents.insert(terminal->getId());

		return adjComponents;
	}

	Type CircuitElement::getPamolaType()
	{
		return Type::CircuitElement;
	}

	uint32_t CircuitElement::getNumberOfTerminals()
	{
		return numberOfterminals;
	}

	bool operator<(const std::shared_ptr<CircuitElement> o1, const std::shared_ptr<CircuitElement> o2)
	{
		return *o1 < *o2;
	}

	bool operator>(const std::shared_ptr<CircuitElement> o1, const std::shared_ptr<CircuitElement> o2)
	{
		return *o1 > *o2;
	}

	bool operator<=(const std::shared_ptr<CircuitElement> o1, const std::shared_ptr<CircuitElement> o2)
	{
		return *o1 <= *o2;
	}

	bool operator>=(const std::shared_ptr<CircuitElement> o1, const std::shared_ptr<CircuitElement> o2)
	{
		return *o1 >= *o2;
	}

	bool operator==(const std::shared_ptr<CircuitElement> o1, const std::shared_ptr<CircuitElement> o2)
	{
		return *o1 == *o2;
	}

	bool operator!=(const std::shared_ptr<CircuitElement> o1, const std::shared_ptr<CircuitElement> o2)
	{
		return *o1 != *o2;
	}
}
