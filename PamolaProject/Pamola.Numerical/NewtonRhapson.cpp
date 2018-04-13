#include "stdafx.h"
#include "NewtonRhapson.h"

namespace SystemSolver
{
	NewtonRhapson::NewtonRhapson()
	{
	}


	NewtonRhapson::~NewtonRhapson()
	{
	}

	double NewtonRhapson::iterate(double x, oneVarFunc f)
	{
		return x - (f(x) / Calculus::deriveAt(x, f));
	}

	std::vector<double> NewtonRhapson::iterate(const std::vector<double> &X, const std::vector<multVarFunc> &F)
	{
		using namespace Eigen;
		Matrix<double, Dynamic, Dynamic> J;
		auto jacob = Calculus::jacobianAt(X, F);
		J = jacob;
		std::vector<double> Y(F.size());
		
		for (int i = 0; i < int(F.size()); i++)
			Y[i] = F[i](X);
		
		/*using namespace boost::qvm;
		inverse(J.);
		return X - inverse(J)*Y;*/
		return { 0.0 };
	}
}