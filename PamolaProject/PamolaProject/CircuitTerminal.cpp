/**
 * Project PamolaCore
 */

#include "stdafx.h"
#include "CircuitTerminal.h"

CircuitTerminal::CircuitTerminal()
{
}

CircuitTerminal::~CircuitTerminal()
{
	disconnect();
}

CircuitElement * CircuitTerminal::getElement()
{
	return element;
}

CircuitNode * CircuitTerminal::getNode()
{
	return node;
}

CircuitNode * CircuitTerminal::connectTo(CircuitTerminal *terminal)
{
	switch (this->isConnected()*2+terminal->isConnected())
	{
	case 0:
	{
		CircuitNode * newNode = new CircuitNode;
		this->connectTo(newNode);
		terminal->connectTo(newNode);
		break; 
	}
	case 1:
		this->connectTo(terminal->node);
		break;
	case 2:
		terminal->connectTo(this->node);
		break;
	case 3:
		if (this->node != terminal->node)
			this->node->connectTo(terminal->node);
		break;
	default:
		return nullptr;;
	}
	
	return this->node;
}

CircuitNode * CircuitTerminal::connectTo(CircuitNode *node)
{
	if (isConnected())
	{
		if (this->node==node)
			return this->node;
		
		disconnect();
	}

	this->node = node;
	this->node->terminals.push_back(this);

	return this->node;
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

	std::vector<CircuitTerminal*> &myNodeTerminals = this->node->terminals;

	auto element = std::find(myNodeTerminals.begin(), myNodeTerminals.end(), this);
	myNodeTerminals.erase(element);

	if (myNodeTerminals.size() == 1)
		myNodeTerminals.at(0)->disconnect();
	else if (myNodeTerminals.size() == 0)
		delete node;


	node = nullptr;
	return true;
}

bool CircuitTerminal::isConnected()
{
	return (node);
}

std::vector<PamolaObject*> CircuitTerminal::getAdjacentComponents()
{
	std::vector<PamolaObject*> result(1 + isConnected());

	result.at(0) = static_cast<PamolaObject*>(getElement());

	if (isConnected())
		result.at(1) = static_cast<PamolaObject*>(getNode());

	return result;
}

PamolaType CircuitTerminal::getPamolaType()
{
	return PamolaType::CircuitTerminal;
}

int CircuitTerminal::getDegreesOfFreedom()
{
	return 2;
}
