#pragma once
#include "Calculator.h"
#include "CalculatorC.h"
#include <Eigen/Dense>

namespace SystemSolver
{
	class NewtonRaphson : public Calculator, public CalculatorC
	{		
	public:
		NewtonRaphson();
		~NewtonRaphson();
		
	public:

		virtual double iterate(double, oneVarFunc);
		virtual Eigen::VectorXd iterate(const Eigen::VectorXd &, const std::vector<multVarFunc> &);

		virtual std::complex<double> iterate(std::complex<double>,
			std::function<std::complex<double>(std::complex<double>)>);

		virtual Eigen::VectorXcd iterate(const Eigen::VectorXcd &,
			const std::vector<std::function<std::complex<double>(const Eigen::VectorXcd &)>> &);
	};
}
