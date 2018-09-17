#pragma once
#include "Dipole.h"

namespace Pamola
{
	class Impedance : public Dipole
	{
	private:

		std::complex<double> impedance;

	public:
		Impedance(std::complex<double> = 0.0);

		std::complex<double> getImpedance();

		void setImpedance(std::complex<double>);

		eqMap getEquations();

		varMap getVariables();

	};
}