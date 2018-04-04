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

	static std::vector<double> gradientAt(const std::vector<double> &, SystemSolver::multVarFunc,
		DerivingMode = DerivingMode::Central, double = 1e-6);

	static SystemSolver::matrix jacobianAt(const std::vector<double> &, std::vector<SystemSolver::multVarFunc>,
		DerivingMode = DerivingMode::Central, double = 1e-6);

};