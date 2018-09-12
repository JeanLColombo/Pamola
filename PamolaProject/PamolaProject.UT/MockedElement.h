#pragma once
#include "..\PamolaProject\PamolaEngine.h"

namespace Pamola
{
	namespace UT
	{
		class MockedElement : public CircuitElement
		{
		public:
			MockedElement(int terminals = 0) : CircuitElement(terminals) {}
			~MockedElement() {}

			varMap getVariables() { return {}; }
			
			int getDegreesOfFreedom() { return 0; }
		};
	}
}
