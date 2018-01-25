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

		std::vector<std::function<std::complex<double>(std::map<std::string, std::complex<double>>)>> getEquations();

		std::set<std::string> getVariables();
		
		int getDegreesOfFreedom();

	};
}

