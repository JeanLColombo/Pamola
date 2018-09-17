#pragma once
#include "Dipole.h"

namespace Pamola
{
	class IdealDCCurrentSource: public Dipole
	{
	private:

		double current;

	public:

		IdealDCCurrentSource(double = 0.0);
		~IdealDCCurrentSource();

		std::shared_ptr<Pamola::CircuitTerminal> getPositive();
		std::shared_ptr<Pamola::CircuitTerminal> getNegative();

		double getCurrent();

		void setCurrent(double);

		eqMap getEquations();

		varMap getVariables();
			
	};
}

