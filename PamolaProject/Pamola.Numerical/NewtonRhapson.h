#pragma once
#include "Calculator.h"
#include <Eigen/Dense>

namespace SystemSolver
{
	class NewtonRhapson : public Calculator
	{		
	public:
		NewtonRhapson();
		~NewtonRhapson();
		
	public:

		virtual double iterate(double, oneVarFunc);
		virtual std::vector<double> iterate(const std::vector<double> &, const std::vector<multVarFunc> &);
	};
}
