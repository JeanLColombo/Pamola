#pragma once
#include "ModelSolver.h"
#include "..\Pamola.Numerical\Imports.h"	

namespace Pamola
{
	using fType = std::function<double(Eigen::VectorXd)>;
	using FType = std::vector<fType>;

	class NewtonRaphsonMS : public ModelSolver
	{
	private:

		SystemSolver::NewtonRaphson newtonRaphson;

	public:

		NewtonRaphsonMS();
		~NewtonRaphsonMS();

		bool SolveSystem(varMap&, eqMap&);

	private:

		//fType fWrapper(varMap&, getterSign&);

		//FType FWrapper(varMap&, eqMap&);
	};
}
