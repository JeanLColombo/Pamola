#pragma once
#include "PamolaObject.h"
#include "CircuitElement.h"
#include <memory>
#include <map>
#include <cassert>


namespace Pamola
{
	class CircuitTerminal;
	class CircuitElement;

	class Engine : public std::enable_shared_from_this<Engine>
	{
		friend class CircuitTerminal;

	private:

		static const std::shared_ptr<Engine> localEngine;

		std::map<uint32_t, std::weak_ptr<Object>> localObjects;

		uint32_t guid;

	protected:

		Engine(uint32_t = 0);

	public:

		~Engine();

		static const std::shared_ptr<Engine> getLocalEngine();

		std::map<uint32_t, std::shared_ptr<Object>> getLocalObjects();
		
		std::shared_ptr<Object> getLocalObject(uint32_t);
		
		template <class TCircuitElement> std::shared_ptr<TCircuitElement> createElement();

	private:

		std::vector<std::shared_ptr<CircuitTerminal>> createTerminalsFor(std::shared_ptr<CircuitElement>);

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