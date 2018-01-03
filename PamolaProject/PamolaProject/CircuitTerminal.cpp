
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
			terminal->connectTo(connectTo(std::shared_ptr<CircuitNode>(new CircuitNode)));
			break;
		}
		case 1:
			connectTo(terminal->getNode());
			break;
		case 2:
			terminal->connectTo(getNode());
			break;
		case 3:
			if (getNode() != terminal->getNode())
				getNode()->connectTo(terminal->getNode());
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
		//node->terminals.push_back(shared_from_this());
		//std::weak_ptr<CircuitTerminal> thisReference = std::make_shared<CircuitTerminal>(this);
		//std::shared_ptr<CircuitTerminal> thisReference(dynamic_cast<CircuitTerminal*>(Engine::getLocalEngine()->getLocalObject(getId())));
		node->terminals.push_back(std::shared_ptr<CircuitTerminal>(dynamic_cast<CircuitTerminal*>(Engine::getLocalEngine()->getLocalObject(getId()))));

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

		//getNode()->terminals.erase(shared_from_this());
		//auto terminalInstance = std::find(getNode()->terminals.begin(), getNode()->terminals.end(), shared_from_this());
		//getNode()->getTerminals();
		//auto index = std::find(getNode()->getTerminals().begin(), getNode()->getTerminals().end(), shared_from_this());
		//getNode()->terminals.erase(static_cast<int>(index));
		//auto localId = getId();
		std::remove_if(getNode()->terminals.begin(), getNode()->terminals.end(), [this](std::weak_ptr<CircuitTerminal> t) {return t.lock()->getId() == getId(); });

		/*int index = 0;
		for (auto &terminal : getNode()->getTerminals())
		{
			if (terminal->getId() == getId())
			{
				getNode()->terminals.erase(getNode()->terminals.begin() + index);
				break;
			}
			index++;
		}*/


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
