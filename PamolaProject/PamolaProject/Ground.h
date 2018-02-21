#pragma once

#include "CircuitElement.h"

namespace Pamola
{
	class Ground : public CircuitElement
	{
	public:
		Ground();
		~Ground();

		std::shared_ptr<Pamola::CircuitTerminal> getTerminal();

		eqMap getEquations();

		std::set<std::string> getVariables();
		
		int getDegreesOfFreedom();

	};
}

