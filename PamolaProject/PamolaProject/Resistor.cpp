#include "stdafx.h"
#include "Resistor.h"
#include "CircuitTerminal.h"

namespace Pamola
{
	Resistor::Resistor(double resistance) : resistance(resistance)
	{
	}

	Resistor::~Resistor()
	{
	}

	double Resistor::getResistance()
	{
		return resistance;
	}

	void Resistor::setResistance(double value)
	{
		resistance = value;
	}

	eqMap Resistor::getEquations()
	{
		eqMap equations; 
		
		equations.push_back(currentCallback());

		equations.push_back(
			[this](varMap m) {
					return m[getLeft()->getVoltageVariable()] - m[getRight()->getVoltageVariable()] - 
						(m[getLeft()->getCurrentVariable()] * m[getResistanceVariable()]);
		});

		equations.push_back(
			[this](varMap m) {
			return m[getResistanceVariable()] - getResistance();
		});

		return equations;
	}

	std::set<std::string> Resistor::getVariables()
	{
		return { "R" };
	}

	std::string Resistor::getResistanceVariable()
	{
		return std::to_string(getId()) + ".R";
	}

	int Resistor::getDegreesOfFreedom()
	{
		return 2;
	}

}