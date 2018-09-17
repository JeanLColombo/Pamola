#pragma once
#include "..\PamolaProject\PamolaEngine.h"

namespace Pamola
{
	namespace UT
	{
		class MockedElement : public CircuitElement
		{
		private:

			std::complex<double> var;

		public:
			MockedElement(int terminals = 0) : var(0.0), CircuitElement(terminals) {}
			~MockedElement() {}

			std::complex<double> getVar() { return var; }
			void setVar(std::complex<double> value) { var = value; }

			varMap getVariables() { 
				return{ std::make_pair([this](std::complex<double> x) {setVar(x); }, 
					[this]() {return getVar(); }) }; }

			eqMap getEquations() { return {}; }
			
			int getDegreesOfFreedom() { return 0; }
		};
	}
}
