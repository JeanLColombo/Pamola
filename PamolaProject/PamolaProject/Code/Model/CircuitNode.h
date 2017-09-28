/**
 * Project PamolaCore
 */

#ifndef _CIRCUITNODE_H
#define _CIRCUITNODE_H

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

	std::vector<CircuitTerminal*> terminals;
	
	std::complex<double> voltage;

public: 

	CircuitNode* connectTo(CircuitNode*);

	std::vector<CircuitTerminal*> getTerminals();
	
	std::complex<double> getVoltage();

	bool setVoltage(std::complex<double>);
	

	int getDegreesOfFreedom();

};

#endif //_CIRCUITNODE_H