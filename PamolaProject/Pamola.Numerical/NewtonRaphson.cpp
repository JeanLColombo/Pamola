#include "stdafx.h"
#include "NewtonRaphson.h"

namespace SystemSolver
{
	NewtonRaphson::NewtonRaphson()
	{
	}


	NewtonRaphson::~NewtonRaphson()
	{
	}

	double NewtonRaphson::iterate(double x, oneVarFunc f)
	{
		return x - (f(x) / Calculus::deriveAt(x, f));
	}

	Eigen::VectorXd NewtonRaphson::iterate(const Eigen::VectorXd &X, const std::vector<multVarFunc> &F)
	{
		using namespace Eigen;
		auto jacob = Calculus::jacobianAt(X, F);
		VectorXd Y(F.size());
		
		for (int i = 0; i < int(F.size()); i++)
			Y[i] = F[i](X);
		

		VectorXd deltaX = jacob.colPivHouseholderQr().solve(Y);

		return X - deltaX;
	}
}