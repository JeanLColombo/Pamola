#pragma once

#include "PamolaObject.h"
#include "CircuitTerminal.h"
#include <vector>

class CircuitTerminal;

class CircuitElement: public PamolaObject, public std::enable_shared_from_this<CircuitElement> 
{

	friend class PamolaEngine;

public:

	using std::enable_shared_from_this<CircuitElement>::shared_from_this;

private:
	
	std::vector<std::shared_ptr<CircuitTerminal>> terminals;

	uint32_t numberOfterminals;

protected:

	CircuitElement(uint32_t = 0);

public:

	virtual ~CircuitElement();

public: 
	
	const std::vector<std::shared_ptr<CircuitTerminal>> getTerminals();

	const std::shared_ptr<CircuitTerminal> getTerminal(uint32_t);

	const std::vector<std::shared_ptr<PamolaObject>> getAdjacentComponents();

	PamolaType getPamolaType();

	uint32_t getNumberOfTerminals();

	virtual int getDegreesOfFreedom() = 0;
	
};