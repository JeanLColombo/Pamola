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

std::vector<double> Calculus::gradientAt(const std::vector<double>& X, SystemSolver::multVarFunc f, 
	DerivingMode m , double tol)
{
	std::vector<double> gradient(X.size());
	std::vector<double> Xaux = X;

	for (int i = 0; i < int(X.size()); i++)
	{
		using namespace SystemSolver;
		oneVarFunc wrap = [&X,&Xaux,i,f](double x) {
			Xaux = X;
			Xaux.at(i) = x;
			return f(Xaux);
		};
		
		gradient.at(i) = deriveAt(X[i], wrap, m, tol);
	}

	return gradient;
}

SystemSolver::matrix Calculus::jacobianAt(const std::vector<double> &X, 
	std::vector<SystemSolver::multVarFunc> F, 
	DerivingMode m, double tol)
{
	using namespace SystemSolver;
	matrix jacobian(F.size());
	
	for (int i = 0; i < int(F.size()); i++)
	{
		jacobian[i] = gradientAt(X, F[i], m, tol);
	}
	
	return jacobian;
}

