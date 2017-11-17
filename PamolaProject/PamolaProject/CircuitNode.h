/**
 * Project PamolaCore
 */

#pragma once

#include "PamolaObject.h"
#include "CircuitTerminal.h"
#include <vector>
#include <complex>

class CircuitTerminal;

class CircuitNode: public PamolaObject, virtual public std::enable_shared_from_this<CircuitNode> 
{
	friend class CircuitTerminal;

public:

	CircuitNode();

public:

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