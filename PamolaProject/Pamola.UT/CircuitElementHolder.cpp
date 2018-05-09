#include "stdafx.h"
#include "CircuitElementHolder.h"

CircuitElementHolder::CircuitElementHolder()
	: CircuitElement(2)
{
}

CircuitElementHolder::~CircuitElementHolder()
{
}

std::shared_ptr<Pamola::CircuitTerminal> CircuitElementHolder::getLeft()
{
	return getTerminal(0);
}

std::shared_ptr<Pamola::CircuitTerminal> CircuitElementHolder::getRight()
{
	return getTerminal(1);
}

Pamola::varMap CircuitElementHolder::getVariables()
{
	return {  };
}

int CircuitElementHolder::getDegreesOfFreedom()
{
	return 2;
}
