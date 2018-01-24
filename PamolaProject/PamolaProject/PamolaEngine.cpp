#include "stdafx.h"
#include "PamolaEngine.h"

namespace Pamola
{
	const std::shared_ptr<Engine> Engine::localEngine(new Engine());

	Engine::Engine(uint32_t firstId) : guid(firstId)
	{
	}

	Engine::~Engine()
	{
	}

	const std::shared_ptr<Engine> Engine::getLocalEngine()
	{
		return localEngine;
	}

	std::map<uint32_t, std::shared_ptr<Object>> Engine::getLocalObjects()
	{
		using namespace cpplinq;
	
		localObjects =
			from(localObjects)
			>> where([](std::pair<uint32_t, std::weak_ptr<Object>> p) { return !p.second.expired(); })
			>> select([](std::pair<uint32_t, std::weak_ptr<Object>> p) { return p.second; })
			>> to_map([](std::weak_ptr<Object> o) {return o.lock()->getId(); });
		
		auto result =
			from(localObjects)
			>> select([](std::pair<uint32_t, std::weak_ptr<Object>> p) {return p.second.lock(); })
			>> to_map([](std::shared_ptr<Object> o) {return o->getId(); });

		return result;
	}

	std::shared_ptr<Object> Engine::getLocalObject(uint32_t id)
	{
		return getLocalObjects()[id];
	}

	std::vector<std::shared_ptr<CircuitTerminal>> Engine::createTerminalsFor(std::shared_ptr<CircuitElement> element)
	{
		std::vector<std::shared_ptr<CircuitTerminal>> result;

		for (uint32_t i = 0; i < element->getNumberOfTerminals(); i++)
		{
			std::shared_ptr<CircuitTerminal> terminal(new CircuitTerminal(element));
			mapObject(terminal);
			result.push_back(terminal);
		}

		return result;
	}

	std::shared_ptr<Circuit> Engine::createCircuit(const std::vector<std::shared_ptr<Object>> elementList)
	{
		auto circuit = std::shared_ptr<Circuit>(new Circuit());
		
		mapObject(circuit);

		circuit->setUp(elementList);

		return circuit;
	}

	std::shared_ptr<CircuitNode> Engine::createNode()
	{
		std::shared_ptr<CircuitNode> node(new CircuitNode);
		mapObject(node);

		return node;
	}
	void Engine::mapObject(std::shared_ptr<Object> object)
	{
		object->id = guid++;
		object->engine = shared_from_this();
		localObjects[object->getId()] = object;
	}
}