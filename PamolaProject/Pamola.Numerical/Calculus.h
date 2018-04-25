#pragma once
#include "Types.h"
#include <math.h>

class Calculus
{
public:

	enum class DerivingMode
	{
		Progressive = 1,
		Central = 0,
		Regressive = -1
	};

	Calculus();
	~Calculus();

	static double deriveAt(double, SystemSolver::oneVarFunc, 
		DerivingMode = DerivingMode::Central, double = 1e-6);

	static std::complex<double> deriveAt(std::complex<double> &,
		std::function<std::complex<double>(std::complex<double>)>,
		DerivingMode = DerivingMode::Central, std::complex<double> = 1e-6*std::complex<double>(1.0, 1.0));
	
	static Eigen::VectorXd gradientAt(const Eigen::VectorXd &, SystemSolver::multVarFunc,
		DerivingMode = DerivingMode::Central, double = 1e-6);

	static Eigen::VectorXcd gradientAt(const Eigen::VectorXcd &, 
		std::function<std::complex<double>(Eigen::VectorXcd &)>,
		DerivingMode = DerivingMode::Central, 
		std::complex<double> = 1e-6*std::complex<double>(1.0, 1.0));

	static Eigen::MatrixXd jacobianAt(const Eigen::VectorXd &, std::vector<SystemSolver::multVarFunc>,
		DerivingMode = DerivingMode::Central, double = 1e-6);

	static Eigen::MatrixXcd jacobianAt(const Eigen::VectorXcd &, 
		std::vector<std::function<std::complex<double>(Eigen::VectorXcd &)>>,
		DerivingMode = DerivingMode::Central, 
		std::complex<double> = 1e-6*std::complex<double>(1.0, 1.0));
};


