#include "stdafx.h"
#include "Circuit.h"
#include "CircuitTerminal.h"

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

	std::vector<std::function<std::complex<double>(std::map<std::string, std::complex<double>>)>> Circuit::getEquations()
	{
		std::vector<std::function<std::complex<double>(std::map<std::string, std::complex<double>>)>> equations;

		for (auto &element : elements)
			for (auto &equation : element->getEquations())
				equations.push_back(equation);

		return equations;
	}

	std::set<std::string> Circuit::getVariables()
	{
		std::set<std::string> setOfVariables;
		for (auto &element : elements)
		{
			for (auto &variable : element->getVariables())
			{
				setOfVariables.insert((std::to_string(element->getId()) + "." + variable));
			}
		}

		return setOfVariables;
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

}
