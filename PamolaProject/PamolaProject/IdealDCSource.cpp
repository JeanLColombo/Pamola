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

	std::vector<std::function<std::complex<double>(std::map<std::string, std::complex<double>>)>> IdealDCSource::getEquations()
	{
		std::vector<std::function<std::complex<double>(std::map<std::string, std::complex<double>>)>> equations;

		equations.push_back(currentCallback());

		equations.push_back(
			[this](std::map<std::string, std::complex<double>> m) {
			return m[getPositive()->getVoltageVariable()] - m[getNegative()->getVoltageVariable()] - m[getVoltageVariable()];
		});

		equations.push_back(
			[this](std::map<std::string, std::complex<double>> m) {
			return m[getVoltageVariable()] - getVoltage();
		});

		return equations;
	}

	std::set<std::string> IdealDCSource::getVariables()
	{
		return { "V" };
	}

	std::string IdealDCSource::getVoltageVariable()
	{
		return std::to_string(getId()) + ".V";
	}

	int IdealDCSource::getDegreesOfFreedom()
	{
		return 2;
	}
}