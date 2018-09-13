#pragma once
#include "..\PamolaProject\PamolaEngine.h"

namespace Pamola
{
	namespace UT
	{
		class MockedModelSolver : public ModelSolver
		{
		public:
			MockedModelSolver() {}
			~MockedModelSolver() {}

			bool SolveSystem(varMap &variables, eqMap &equations)
			{
				using namespace std::complex_literals;
				for (auto &var : variables)
					var.first(4. + 3i);

				return true;
			}
		};
	}
}