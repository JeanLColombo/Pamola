#pragma once
#include "PamolaTypes.h"
#include "ModelSolver.h"

namespace Pamola
{
	class MockedModelSolver : public ModelSolver
	{
	public:
		MockedModelSolver();
		~MockedModelSolver();
	
		bool SolveSystem(varMap&, eqMap&);
	};
}
