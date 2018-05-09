#pragma once
#include "PamolaTypes.h"

namespace Pamola
{
	class ModelSolver
	{
	public:

		ModelSolver();

		virtual ~ModelSolver();
		
		virtual bool SolveSystem(varMap&, eqMap&) = 0;
	};
}
