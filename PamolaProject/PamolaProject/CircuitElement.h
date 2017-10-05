/**
 * Project PamolaCore
 */

#pragma once

#include "PamolaObject.h"
#include "CircuitTerminal.h"
#include <vector>

class CircuitTerminal;

class CircuitElement: public PamolaObject {
protected:

	CircuitElement();
	~CircuitElement();

private:
	
	std::vector<CircuitTerminal*> terminals;

protected:

	bool createTerminals(uint32_t);

public: 
	
	std::vector<CircuitTerminal*> getTerminals();

	CircuitTerminal* getTerminal(uint32_t);

	virtual int getDegreesOfFreedom() = 0;
	
};