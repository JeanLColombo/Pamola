#pragma once

#include "PamolaObject.h"
#include <set>
#include <complex>

class CircuitTerminal;

class CircuitNode: public PamolaObject, public std::enable_shared_from_this<CircuitNode> 
{
	using std::enable_shared_from_this<CircuitNode>::shared_from_this;
	
	friend class CircuitTerminal;

private:

	std::set<std::shared_ptr<CircuitTerminal>> terminals;
	
	std::complex<double> voltage;

	CircuitNode();

public:

	~CircuitNode();

public: 

	std::shared_ptr<CircuitNode> connectTo(std::shared_ptr<CircuitNode>);

	const std::vector<std::shared_ptr<CircuitTerminal>> getTerminals();
	
	std::complex<double> getVoltage();

	bool setVoltage(std::complex<double>);	

	const std::vector<std::shared_ptr<PamolaObject>> getAdjacentComponents();

	PamolaType getPamolaType();

	int getDegreesOfFreedom();

};