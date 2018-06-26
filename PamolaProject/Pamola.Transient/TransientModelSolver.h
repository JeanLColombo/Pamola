#pragma once
#include "Types.h"

namespace Pamola
{
	class TransientModelSolver
	{
	public:
		TransientModelSolver();
		virtual ~TransientModelSolver();
		// TODO: Create Integrate Signature
		virtual std::map<double, std::vector<std::complex<double>>> Integrate() = 0;
	};
}
