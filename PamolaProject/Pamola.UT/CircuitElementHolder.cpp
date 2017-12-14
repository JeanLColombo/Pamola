#include "stdafx.h"
#include "CircuitElementHolder.h"

CircuitElementHolder::CircuitElementHolder()
	: CircuitElement(2)
{
}

CircuitElementHolder::~CircuitElementHolder()
{
}

std::shared_ptr<CircuitTerminal> CircuitElementHolder::getLeft()
{
	return getTerminal(0);
}

std::shared_ptr<CircuitTerminal> CircuitElementHolder::getRight()
{
	return getTerminal(1);
}

int CircuitElementHolder::getDegreesOfFreedom()
{
	return 2;
}
