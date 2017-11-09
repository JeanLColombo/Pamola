/**
 * Project PamolaCore
 */

#pragma once

#include "PamolaObject.h"
#include "CircuitTerminal.h"
#include <vector>
#include <complex>

class CircuitNode: public PamolaObject {

	friend class CircuitTerminal;

protected:

	CircuitNode();
	~CircuitNode();

private:

	std::vector<std::weak_ptr<CircuitTerminal>> terminals;
	
	std::complex<double> voltage;

public: 

	CircuitNode & connectTo(CircuitNode &);

	const std::vector<std::shared_ptr<CircuitTerminal>> getTerminals();
	
	std::complex<double> getVoltage();

	bool setVoltage(std::complex<double>);	

	const std::vector<std::shared_ptr<PamolaObject>> getAdjacentComponents();

	PamolaType getPamolaType();

	int getDegreesOfFreedom();
};