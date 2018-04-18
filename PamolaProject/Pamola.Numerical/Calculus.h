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

	static Eigen::VectorXd gradientAt(const Eigen::VectorXd &, SystemSolver::multVarFunc,
		DerivingMode = DerivingMode::Central, double = 1e-6);

	static Eigen::MatrixXd jacobianAt(const Eigen::VectorXd &, std::vector<SystemSolver::multVarFunc>,
		DerivingMode = DerivingMode::Central, double = 1e-6);

};