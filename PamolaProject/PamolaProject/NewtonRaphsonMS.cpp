#include "stdafx.h"
#include "NewtonRaphsonMS.h"

namespace Pamola
{
	NewtonRaphsonMS::NewtonRaphsonMS()
	{
	}


	NewtonRaphsonMS::~NewtonRaphsonMS()
	{
	}

	bool NewtonRaphsonMS::SolveSystem(varMap &variables, eqMap &equations)
	{
		auto F = FWrapper(variables, equations);
		
		using namespace Eigen;
		using namespace std::literals;

		VectorXcd X0 = (VectorXcd::Ones(variables.size()))*(1.0 + 1.0i);

		double error = 1.0;
		int i = 0;

		while (error >= 1.0e-6 && i < 100)
		{
			auto X1 = newtonRaphson.iterate(X0, F);
			auto complexError = (X1 - X0).dot(X1 - X0);
			error = pow(complexError.real(), 2.0) + pow(complexError.imag(), 2.0);
			X0 = X1;
		}

		if (error >= 1.0e-6 && i>=100)
			return false;

		for (int i = 0; i < int(variables.size()); i++)
			variables[i].first(X0(i));

		return true;
	}

	std::function<std::complex<double>(const Eigen::VectorXcd&)> NewtonRaphsonMS::fWrapper(varMap &variables, 
		getterSign &equation)
	{
		auto result = [variables, equation](const Eigen::VectorXcd X) {

			for (int i = 0; i < X.size(); i++)
				variables.at(i).first(X(i));
			
			return equation();
		};

		return result;
	}

	std::vector<std::function<std::complex<double>(const Eigen::VectorXcd&)>> 
		NewtonRaphsonMS::FWrapper(varMap &variables, 
			eqMap &equations)
	{		
		std::vector<std::function<std::complex<double>(const Eigen::VectorXcd&)>> result(equations.size());

		for (int i = 0; i < int(equations.size()); i++)
			result[i] = fWrapper(variables, equations[i]);

		return result;
	}
}