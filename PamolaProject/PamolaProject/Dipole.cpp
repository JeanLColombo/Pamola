#include "stdafx.h"
#include "Dipole.h"
#include "CircuitTerminal.h"

namespace Pamola {

	Dipole::Dipole() : CircuitElement(2)
	{
	}


	Dipole::~Dipole()
	{
	}

	std::shared_ptr<Pamola::CircuitTerminal> Dipole::getLeft()
	{
		return getTerminal(0);
	}

	std::shared_ptr<Pamola::CircuitTerminal> Dipole::getRight()
	{
		return getTerminal(1);
	}

	std::function<std::complex<double>(varMap)> Dipole::currentCallback()
	{
		return [this](varMap m) {
			return m[std::to_string(getLeft()->getId()) + ".I"]	+ m[std::to_string(getRight()->getId()) + ".I"]; };
	}

	void Dipole::connectInSeriesTo(std::shared_ptr<Dipole> dipole)
	{
		getRight()->connectTo(dipole->getLeft());
	}

	void Dipole::connectInParallelTo(std::shared_ptr<Dipole> dipole)
	{
		getRight()->connectTo(dipole->getRight());
		getLeft()->connectTo(dipole->getLeft());
	}
	
}