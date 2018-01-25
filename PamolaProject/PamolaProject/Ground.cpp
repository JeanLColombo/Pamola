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

	std::vector<std::function<std::complex<double>(std::map<std::string, std::complex<double>>)>> Ground::getEquations()
	{
		return { [this](std::map<std::string, std::complex<double>> m){
			return m[getTerminal()->getVoltageVariable()]; } };
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
