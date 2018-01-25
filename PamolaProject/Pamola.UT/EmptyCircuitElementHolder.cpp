#include "stdafx.h"
#include "EmptyCircuitElementHolder.h"

EmptyCircuitElementHolder::EmptyCircuitElementHolder()
{
}

EmptyCircuitElementHolder::~EmptyCircuitElementHolder()
{
}

std::set<std::string> EmptyCircuitElementHolder::getVariables()
{
	return { "R" };
}

int EmptyCircuitElementHolder::getDegreesOfFreedom()
{
	return 0;
}
