/**
 * Project PamolaCore
 */

#pragma once

#include "PamolaObject.h"
#include "CircuitTerminal.h"
#include <vector>

class CircuitTerminal;

class CircuitElement: public PamolaObject, virtual public std::enable_shared_from_this<CircuitElement> 
{
protected:

	CircuitElement();

public:

	~CircuitElement();

private:
	
	std::vector<std::shared_ptr<CircuitTerminal>> terminals;

protected:

	bool createTerminals(uint32_t);

public: 
	
	const std::vector<std::shared_ptr<CircuitTerminal>> getTerminals();

	const std::shared_ptr<CircuitTerminal> getTerminal(uint32_t);

	const std::vector<std::shared_ptr<PamolaObject>> getAdjacentComponents();

	PamolaType getPamolaType();

	virtual int getDegreesOfFreedom() = 0;
	
};