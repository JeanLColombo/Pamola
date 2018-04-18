#pragma once
#include "Calculator.h"
#include <Eigen/Dense>

namespace SystemSolver
{
	class NewtonRaphson : public Calculator
	{		
	public:
		NewtonRaphson();
		~NewtonRaphson();
		
	public:

		virtual double iterate(double, oneVarFunc);
		virtual Eigen::VectorXd iterate(const Eigen::VectorXd &, const std::vector<multVarFunc> &);
	};
}
