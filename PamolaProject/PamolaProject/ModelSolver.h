#pragma once
#include "PamolaTypes.h"

namespace Pamola
{
	class ModelSolver
	{
	protected:
		ModelSolver();

	public:
		virtual ~ModelSolver();
		
		virtual varMap SolveSystem(varMap, eqMap) = 0;
	};
}
