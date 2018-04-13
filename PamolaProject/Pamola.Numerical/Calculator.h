#pragma once
#include <vector>
#include "Types.h"
#include "Calculus.h"

namespace SystemSolver
{
	class Calculator
	{
	public:
		Calculator();
		virtual ~Calculator();
	
		virtual double iterate(double, oneVarFunc) = 0;
		virtual std::vector<double> iterate(const std::vector<double> &, const std::vector<multVarFunc> &) = 0;
	
	};
}

