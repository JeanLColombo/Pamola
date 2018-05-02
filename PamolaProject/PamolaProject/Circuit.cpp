#include "stdafx.h"
#include "Circuit.h"
#include "CircuitTerminal.h"
#include "PamolaEngine.h"

namespace Pamola
{
	Circuit::Circuit()
	{
	}

	Circuit::~Circuit()
	{
	}

	const std::set<std::shared_ptr<CircuitTerminal>> Circuit::getTerminals()
	{
		return terminals;
	}

	const std::set<std::shared_ptr<Object>> Circuit::getElements()
	{
		return elements;
	}

	eqMap Circuit::getEquations()
	{
		eqMap equations;

		for (auto &element : elements)
			for (auto &equation : element->getEquations())
				equations.push_back(equation);

		return equations;
	}

	varMap Circuit::getVariables()
	{
		varMap mapOfVariables;
		for (auto &element : elements)
		{
			for (auto &variable : element->getVariables())
			{
				mapOfVariables.push_back(variable);
			}
		}
		return mapOfVariables;
	}

	const std::set<uint32_t> Circuit::getAdjacentComponents()
	{
		//TODO: Check what we desire to output from this method
		return { 0 };
	}

	Type Circuit::getPamolaType()
	{
		return Type::Circuit;
	}

	int Circuit::getDegreesOfFreedom()
	{
		int result(0);

		for (auto &element : getElements())
			result += element->getDegreesOfFreedom();

		return result;
	}

	void Circuit::setUp(const std::vector<std::shared_ptr<Object>> &circuitList)
	{
		for (const auto &element : circuitList)
		{
			elements.insert(element);
			if (element->getPamolaType() == Type::CircuitTerminal)
			{
				auto foundTerminal = std::dynamic_pointer_cast<CircuitTerminal>(element);
				
				if (!foundTerminal->isConnected())
					terminals.insert(foundTerminal);
			}
		}
	}

	void Circuit::solve()
	{
		getEngine()->callSolver(getVariables(), getEquations());
	}

}
