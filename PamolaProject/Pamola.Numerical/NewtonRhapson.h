#pragma once
#include "Calculator.h"

namespace SystemSolver
{
	class NewtonRhapson : public Calculator
	{
	public:
		NewtonRhapson();
		~NewtonRhapson();
		
	public:

		virtual double iterate(double, oneVarFunc);
		
	};
}
