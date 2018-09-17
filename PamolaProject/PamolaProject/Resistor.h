#pragma once

#include "Dipole.h"

namespace Pamola
{
	class Resistor : public Dipole
	{
	private:

		double resistance;

	public:

		Resistor(double = 1.0);
		~Resistor();

		double getResistance();

		void setResistance(double);

		eqMap getEquations();

		varMap getVariables();
	};
}