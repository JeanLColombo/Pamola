#include "stdafx.h"
#include "EmptyCircuitElementHolder.h"

EmptyCircuitElementHolder::EmptyCircuitElementHolder()
{
}

EmptyCircuitElementHolder::~EmptyCircuitElementHolder()
{
}

Pamola::varMap EmptyCircuitElementHolder::getVariables()
{
	return { };
}

int EmptyCircuitElementHolder::getDegreesOfFreedom()
{
	return 0;
}
