#pragma once
#include "PamolaObject.h"
#include <memory>
#include <set>
#include <cassert>


namespace Pamola
{
	class Engine
	{

		friend class Object;

	private:

		static const std::shared_ptr<Engine> localEngine;

		std::set<Object*> localObjects;

	protected:

		Engine();

	public:

		~Engine();

		static const std::shared_ptr<Engine> getLocalEngine();

		const std::set<Object*> getLocalObjects();

		Object* getLocalObject(uint32_t);

		template <class TCircuitElement> std::shared_ptr<TCircuitElement> createElement();
	};

	template<class TCircuitElement>
	inline std::shared_ptr<TCircuitElement> Engine::createElement()
	{
		std::shared_ptr<TCircuitElement> newElement(new TCircuitElement());
		assert(static_cast<std::shared_ptr<CircuitElement>>(newElement) && "TCircuitElement must inherit from CircuitElement");

		std::shared_ptr<CircuitElement> newCircuitElement = newElement;

		for (uint32_t i = 0; i < newCircuitElement->getNumberOfTerminals(); i++)
			newCircuitElement->terminals.push_back(std::shared_ptr<CircuitTerminal>(new CircuitTerminal(newCircuitElement)));

		return newElement;
	}

	template<class TCircuitElement>
	std::shared_ptr<TCircuitElement> createElement()
	{
		return Engine::getLocalEngine()->createElement<TCircuitElement>();
	}
}