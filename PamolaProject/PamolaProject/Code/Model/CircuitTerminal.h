/**
 * Project PamolaCore
 */

#ifndef _CIRCUITTERMINAL_H
#define _CIRCUITTERMINAL_H

#include "PamolaObject.h"
#include "CircuitElement.h"
#include "CircuitNode.h"
#include <complex>


class CircuitTerminal: public PamolaObject {

	friend class CircuitElement;

protected:

	CircuitTerminal();
	~CircuitTerminal();
	
private:

	CircuitElement *element;
	CircuitNode *node = nullptr;

	std::complex<double> current = 0.0;

public: 
	
	CircuitElement* getElement();
	CircuitNode* getNode();
	CircuitNode* connectTo(CircuitTerminal*);
	CircuitNode* connectTo(CircuitNode*);

	std::complex<double> getCurrent();
	std::complex<double> getVoltage();

	bool setCurrent(std::complex<double>);
	bool disconnect();
	bool isConnected();

	int getDegreesOfFreedom();

};
#endif //_CIRCUITTERMINAL_H