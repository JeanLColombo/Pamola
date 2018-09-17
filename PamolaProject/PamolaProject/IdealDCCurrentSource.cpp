#include "stdafx.h"
#include "IdealDCCurrentSource.h"
#include "CircuitTerminal.h"

namespace Pamola
{
	IdealDCCurrentSource::IdealDCCurrentSource(double current)
		: current(current)
	{
	}
	IdealDCCurrentSource::~IdealDCCurrentSource()
	{
	}
	std::shared_ptr<Pamola::CircuitTerminal> IdealDCCurrentSource::getPositive()
	{
		return getRight();
	}
	std::shared_ptr<Pamola::CircuitTerminal> IdealDCCurrentSource::getNegative()
	{
		return getLeft();
	}
	double IdealDCCurrentSource::getCurrent()
	{
		return current;
	}
	void IdealDCCurrentSource::setCurrent(double value)
	{
		current = value;
	}
	eqMap IdealDCCurrentSource::getEquations()
	{
		eqMap equations;

		equations.push_back(currentCallback());

		equations.push_back(
			[this]() {
			return getNegative()->getCurrent() - getCurrent();
		});

		return equations;
	}
	varMap IdealDCCurrentSource::getVariables()
	{
		return {};
	}
	
}