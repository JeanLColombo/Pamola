#include "stdafx.h"
#include "Impedance.h"
#include "CircuitTerminal.h"

namespace Pamola
{
	Impedance::Impedance(std::complex<double> impedance) : impedance(impedance)
	{
	}
	std::complex<double> Impedance::getImpedance()
	{
		return impedance;
	}
	void Impedance::setImpedance(std::complex<double> value)
	{
		impedance = value;
	}
	eqMap Impedance::getEquations()
	{
		eqMap equations;

		equations.push_back(currentCallback());

		equations.push_back(
			[this]() {
			return getLeft()->getVoltage() - getRight()->getVoltage() -
				(getLeft()->getCurrent() * getImpedance());
		});

		return equations;
	}
	varMap Impedance::getVariables()
	{
		return {};
	}
	int Impedance::getDegreesOfFreedom()
	{
		return 2;
	}
}