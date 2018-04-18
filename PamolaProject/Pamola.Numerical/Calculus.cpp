#include "stdafx.h"
#include "Calculus.h"


Calculus::Calculus()
{
}

Calculus::~Calculus()
{
}

double Calculus::deriveAt(double x, SystemSolver::oneVarFunc f, 
	DerivingMode m, double tol)
{
	double xNext = x, xPrev = x, yNext, yPrev;

	switch (m)
	{
	case Calculus::DerivingMode::Progressive:	xNext += tol;				break;
	case Calculus::DerivingMode::Central:		xNext += tol; xPrev -= tol; break;
	case Calculus::DerivingMode::Regressive:	xPrev -= tol;				break;
	default:									xNext += tol; xPrev -= tol; break;
	}

	yNext = f(xNext); 
	yPrev = f(xPrev);

	return (yNext - yPrev) / (xNext - xPrev);
}

Eigen::VectorXd Calculus::gradientAt(const Eigen::VectorXd &X, SystemSolver::multVarFunc f,
	DerivingMode m, double tol)
{
	Eigen::VectorXd gradient(X.size());
	Eigen::VectorXd Xaux = X;

	for (int i = 0; i < int(X.size()); i++)
	{
		using namespace SystemSolver;
		oneVarFunc wrap = [&X, &Xaux, i, f](double x) {
			Xaux = X;
			Xaux(i) = x;
			return f(Xaux);
		};

		gradient(i) = deriveAt(X(i), wrap, m, tol);
	}

	return gradient;
}

Eigen::MatrixXd Calculus::jacobianAt(const Eigen::VectorXd &X,
	std::vector<SystemSolver::multVarFunc> F, 
	DerivingMode m, double tol)
{
	using namespace SystemSolver;
	Eigen::MatrixXd jacobian(F.size(), X.size());

	for (int i = 0; i < int(F.size()); i++)
		jacobian.row(i) = gradientAt(X, F[i], m, tol);
	
	return jacobian;
}

