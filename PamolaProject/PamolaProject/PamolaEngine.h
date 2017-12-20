#pragma once
#include "PamolaObject.h"
#include <memory>
#include <set>
#include <cassert>

class PamolaEngine
{

	friend class PamolaObject;

private:

	static const std::shared_ptr<PamolaEngine> localEngine;

	std::set<PamolaObject*> localObjects;

protected:

	PamolaEngine();

public:

	~PamolaEngine();

	static const std::shared_ptr<PamolaEngine> getLocalEngine();

	const std::set<PamolaObject*> getLocalObjects();

	template <class TCircuitElement> std::shared_ptr<TCircuitElement> createElement();
};

template<class TCircuitElement>
inline std::shared_ptr<TCircuitElement> PamolaEngine::createElement()
{
	std::shared_ptr<TCircuitElement> newElement(new TCircuitElement());
	assert(dynamic_cast<std::shared_ptr<CircuitElement>>(newElement) && "TCircuitElement must inherit from CircuitElement");

	std::shared_ptr<CircuitElement> newCircuitElement = newElement;
	
	for (uint32_t i = 0; i < newCircuitElement->getNumberOfTerminals(); i++)
		newCircuitElement->terminals.push_back(std::shared_ptr<CircuitTerminal>(new CircuitTerminal(newCircuitElement)));

	return newElement;
}
