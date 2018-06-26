#pragma once
#include "Types.h"
#include "TransientModelSolver.h"

namespace Pamola
{
	class TransientFacade
	{
	private:
		
		std::shared_ptr<Circuit> circuit;

		std::shared_ptr<TransientModelSolver> transientModelSolver;

		std::map<double, std::vector<std::complex<double>>> transientMap;

	public:

		TransientFacade(std::shared_ptr<Circuit>, std::shared_ptr<TransientModelSolver>);
		
		~TransientFacade();
	};


	// Facade Creators
	//std::unique_ptr<TransientFacade> getAsTransient(std::shared_ptr<Circuit>);

	std::unique_ptr<TransientFacade> getAsTransient(std::shared_ptr<Circuit>, std::shared_ptr<TransientModelSolver>);

}