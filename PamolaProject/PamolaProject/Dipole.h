#pragma once

#include "CircuitElement.h"

namespace Pamola {
	
	class Dipole : public CircuitElement
	{
	public:
		Dipole();
		virtual ~Dipole();

		std::shared_ptr<Pamola::CircuitTerminal> getLeft();
		std::shared_ptr<Pamola::CircuitTerminal> getRight();
		
	protected:

		std::function<std::complex<double>(std::map<std::string, std::complex<double>>)> currentCallback();

	public:

		virtual std::set<std::string> getVariables() = 0;

		virtual int getDegreesOfFreedom() = 0;
	};
}
