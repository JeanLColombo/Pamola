#pragma once
#include "ModelSolver.h"
#include "..\Pamola.Numerical\Imports.h"	

namespace Pamola
{
	class NewtonRaphsonMS : public ModelSolver
	{
	private:

		SystemSolver::NewtonRaphson newtonRaphson;

	public:

		NewtonRaphsonMS();
		~NewtonRaphsonMS();

		bool SolveSystem(varMap&, eqMap&);

	private:

		std::function<std::complex<double>(const Eigen::VectorXcd&)> fWrapper(varMap&, getterSign&);

		std::vector<std::function<std::complex<double>(const Eigen::VectorXcd&)>> FWrapper(varMap&, eqMap&);
	};
}
