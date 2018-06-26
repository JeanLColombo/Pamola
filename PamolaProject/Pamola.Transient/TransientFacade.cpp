#include "stdafx.h"
#include "TransientFacade.h"


namespace Pamola
{
	


	TransientFacade::TransientFacade(std::shared_ptr<Circuit> circuit, std::shared_ptr<TransientModelSolver> modelSolver)
		: circuit(circuit), transientModelSolver(modelSolver)
	{
	}

	TransientFacade::~TransientFacade()
	{
	}


	std::unique_ptr<TransientFacade> getAsTransient(std::shared_ptr<Circuit> circuit, std::shared_ptr<TransientModelSolver> modelSolver)
	{
		return 	std::make_unique<TransientFacade>(circuit, modelSolver);
	}
}