#include "stdafx.h"
#include "MockedModelSolver.h"


namespace Pamola
{
	MockedModelSolver::MockedModelSolver()
	{
	}

	MockedModelSolver::~MockedModelSolver()
	{
	}

	bool MockedModelSolver::SolveSystem(varMap &variables, eqMap &equations)
	{
		using namespace std::complex_literals;
		for (auto &var : variables)
			var.first(4. + 3i);

		return true;
	}


}
