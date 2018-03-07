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

	getterSign Dipole::currentCallback()
	{
		return [this]() {
			return getLeft()->getCurrent() + getRight()->getCurrent(); };
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