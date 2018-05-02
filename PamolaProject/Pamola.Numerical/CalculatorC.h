#pragma once
#include <vector>
#include <complex>
#include "Types.h"
#include "Calculus.h"

namespace SystemSolver
{
	class CalculatorC
	{
	public:
		CalculatorC();
		virtual ~CalculatorC();

		virtual std::complex<double> iterate(std::complex<double>,
			std::function<std::complex<double>(std::complex<double>)>) = 0;
		virtual Eigen::VectorXcd iterate(const Eigen::VectorXcd &,
			const std::vector<std::function<std::complex<double>(const Eigen::VectorXcd &)>> &) = 0;

	};
}

