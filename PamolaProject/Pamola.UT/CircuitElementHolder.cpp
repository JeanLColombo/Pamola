#include "stdafx.h"
#include "CircuitElementHolder.h"

CircuitElementHolder::CircuitElementHolder()
{
	createTerminals(2);
}

CircuitElementHolder::~CircuitElementHolder()
{
}

std::shared_ptr<CircuitTerminal> CircuitElementHolder::getLeft()
{
	return getTerminal(0).shared_from_this();
}

std::shared_ptr<CircuitTerminal> CircuitElementHolder::getRight()
{
	return getTerminal(1).shared_from_this();
}

int CircuitElementHolder::getDegreesOfFreedom()
{
	return 2;
}
