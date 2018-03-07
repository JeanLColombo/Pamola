#include "stdafx.h"
#include "Ground.h"
#include "CircuitTerminal.h"

namespace Pamola
{
	Ground::Ground() : CircuitElement(1)
	{
	}

	Ground::~Ground()
	{
	}

	std::shared_ptr<Pamola::CircuitTerminal> Ground::getTerminal()
	{
		return CircuitElement::getTerminal(0);
	}

	eqMap Ground::getEquations()
	{
		return { [this](){
			return getTerminal()->getVoltage(); } };
	}

	std::set<std::string> Ground::getVariables()
	{
		return {};
	}
	int Ground::getDegreesOfFreedom()
	{
		return -1;
	}
}
