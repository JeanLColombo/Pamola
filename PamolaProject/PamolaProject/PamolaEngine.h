#pragma once

#include "PamolaTypes.h"
#include "PamolaObject.h"
#include "CircuitElement.h"
#include "CircuitTerminal.h"
#include "CircuitNode.h"
#include "Circuit.h"
#include "Dipole.h"
#include "Resistor.h"
#include "IdealDCSource.h"
#include "Ground.h"
#include "ModelSolver.h"
#include "MockedModelSolver.h"
#include "NewtonRaphsonMS.h"
#include <memory>
#include <map>
#include <cassert>


namespace Pamola
{
	class CircuitTerminal;
	class CircuitElement;
	class Circuit;
	class Object;

	class Engine : public std::enable_shared_from_this<Engine>
	{
		friend class CircuitTerminal;
		friend class Object;

	private:

		static const std::shared_ptr<Engine> localEngine;

		std::map<uint32_t, std::weak_ptr<Object>> localObjects;

		std::shared_ptr<ModelSolver> solver;

		uint32_t guid;

	protected:

		Engine(uint32_t = 0);

	public:

		~Engine();

		static const std::shared_ptr<Engine> getLocalEngine();

		std::map<uint32_t, std::shared_ptr<Object>> getLocalObjects();
		
		std::shared_ptr<Object> getLocalObject(uint32_t);

		std::shared_ptr<ModelSolver> getSolver();

		void setSolver(std::shared_ptr<ModelSolver>);
		
		void callSolver(varMap&, eqMap&);

		template <class TCircuitElement> std::shared_ptr<TCircuitElement> createElement();

	private:

		std::vector<std::shared_ptr<CircuitTerminal>> createTerminalsFor(std::shared_ptr<CircuitElement>);

		std::shared_ptr<Circuit> createCircuit(const std::vector<std::shared_ptr<Object>>);

		std::shared_ptr<CircuitNode> createNode();
		
		void mapObject(std::shared_ptr<Object>);
	};

	template<class TCircuitElement>
	inline std::shared_ptr<TCircuitElement> Engine::createElement()
	{
		std::shared_ptr<TCircuitElement> newElement(new TCircuitElement());
		assert(static_cast<std::shared_ptr<CircuitElement>>(newElement) && "TCircuitElement must inherit from CircuitElement");

		std::shared_ptr<CircuitElement> newCircuitElement = newElement;

		mapObject(newCircuitElement);

		newCircuitElement->terminals = createTerminalsFor(newCircuitElement);

		return newElement;
	}

	template<class TCircuitElement>
	std::shared_ptr<TCircuitElement> createElement()
	{
		return Engine::getLocalEngine()->createElement<TCircuitElement>();
	}
}
