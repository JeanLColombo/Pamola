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

		std::vector<std::function<std::complex<double>(std::map<std::string, std::complex<double>>)>> getEquations();

		std::set<std::string> getVariables();

		std::string getResistanceVariable();

		int getDegreesOfFreedom();
	};
}