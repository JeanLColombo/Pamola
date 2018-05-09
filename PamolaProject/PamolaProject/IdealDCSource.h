#pragma once

#include "Dipole.h"

namespace Pamola
{
	class IdealDCSource : public Dipole
	{
	private:

		double voltage;

	public:
		IdealDCSource(double = 0.0);
		~IdealDCSource();

		std::shared_ptr<Pamola::CircuitTerminal> getPositive();
		std::shared_ptr<Pamola::CircuitTerminal> getNegative();

		double getVoltage();

		void setVoltage(double);

		eqMap getEquations();

		varMap getVariables();

		std::string getVoltageVariable();

		int getDegreesOfFreedom();

	};
}
