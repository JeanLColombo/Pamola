
#include "stdafx.h"
#include "CircuitTerminal.h"

namespace Pamola
{
	CircuitTerminal::CircuitTerminal(std::weak_ptr<CircuitElement> ownerElement)
		: element(ownerElement)
	{
	}

	CircuitTerminal::~CircuitTerminal()
	{
		disconnect();
	}

	const std::shared_ptr<CircuitElement> CircuitTerminal::getElement()
	{
		return element.lock();
	}

	std::shared_ptr<CircuitNode> CircuitTerminal::getNode()
	{
		return node;
	}

	std::shared_ptr<CircuitNode> CircuitTerminal::connectTo(std::shared_ptr<CircuitTerminal> terminal)
	{	
		switch (isConnected() * 2 + terminal->isConnected())
		{
		case 0:
		{
			terminal->connectTo(this->connectTo(this->getEngine()->createNode()));
			break;
		}
		case 1:
			this->connectTo(terminal->getNode());
			break;
		case 2:
			terminal->connectTo(getNode());
			break;
		case 3:
			if (this->getNode() != terminal->getNode())
				this->getNode()->connectTo(terminal->getNode());
			break;
		default:
			assert("Impossible value on terminal connection");
		}

		return getNode();
	}

	std::shared_ptr<CircuitNode> CircuitTerminal::connectTo(std::shared_ptr<CircuitNode> node)
	{
		if (isConnected())
		{
			if (node == getNode())
				return node;

			disconnect();
		}

		this->node = node;
		node->terminals.push_back(shared_from_this());

		return node;
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
		if (!isConnected())
			return false;

	
		for (uint32_t i = 0; i < this->getNode()->getTerminals().size(); i++)
		{
			if (this->getId() == getNode()->terminals[i].lock()->getId())
			{		
				this->getNode()->terminals.erase(this->getNode()->terminals.begin() + i);
				break;
			}
		}
				
		if (getNode()->getTerminals().size() == 1)
			getNode()->getTerminals().at(0)->disconnect();

		node = nullptr;
		return true;
	}

	bool CircuitTerminal::isConnected()
	{
		return static_cast<bool>(getNode());
	}

	const std::vector<std::shared_ptr<Object>> CircuitTerminal::getAdjacentComponents()
	{
		std::vector<std::shared_ptr<Object>> result(1 + isConnected());

		result.at(0) = static_cast<std::shared_ptr<Object>>(getElement());

		if (isConnected())
			result.at(1) = node;

		return result;
	}

	Type CircuitTerminal::getPamolaType()
	{
		return Type::CircuitTerminal;
	}

	int CircuitTerminal::getDegreesOfFreedom()
	{
		return 2;
	}
}
