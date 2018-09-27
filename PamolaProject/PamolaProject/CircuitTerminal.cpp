
#include "stdafx.h"
#include "CircuitTerminal.h"
#include "CircuitElement.h"
#include "CircuitNode.h"
#include "PamolaEngine.h"

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
		if (terminal == shared_from_this())
			return getNode();

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
		}

		return getNode();
	}

	std::shared_ptr<CircuitNode> CircuitTerminal::connectTo(std::shared_ptr<CircuitNode> node)
	{

		if (isConnected())
		{
			if (node == getNode())
				return node;

			return getNode()->connectTo(node);
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
			return std::complex<double>(NAN, NAN);

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

	varMap CircuitTerminal::getVariables()
	{
		return { std::make_pair([this](std::complex<double> x) {setCurrent(x); },
			[this]() {return getCurrent(); }) };
	}

	const std::set<uint32_t> CircuitTerminal::getAdjacentComponents()
	{
		std::set<uint32_t> adjComponents;

		adjComponents.insert(getElement()->getId());

		if (isConnected())
			adjComponents.insert(getNode()->getId());

		return adjComponents;
	}

	Type CircuitTerminal::getPamolaType()
	{
		return Type::CircuitTerminal;
	}

}
