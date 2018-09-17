#include "stdafx.h"
#include "IdealDCSource.h"
#include "CircuitTerminal.h"

namespace Pamola
{
	IdealDCSource::IdealDCSource(double ddp) : voltage(ddp)
	{
	}

	IdealDCSource::~IdealDCSource()
	{
	}

	std::shared_ptr<Pamola::CircuitTerminal> IdealDCSource::getPositive()
	{
		return getLeft();
	}

	std::shared_ptr<Pamola::CircuitTerminal> IdealDCSource::getNegative()
	{
		return getRight();
	}

	double IdealDCSource::getVoltage()
	{
		return voltage;
	}

	void IdealDCSource::setVoltage(double value)
	{
		voltage = value;
	}

	eqMap IdealDCSource::getEquations()
	{
		eqMap equations;

		equations.push_back(currentCallback());

		equations.push_back(
			[this]() {
			return getPositive()->getVoltage() - getNegative()->getVoltage() - getVoltage();
		});

		return equations;
	}

	varMap IdealDCSource::getVariables()
	{
		return {};
	}

}