/**
 * Project PamolaCore
 */


#ifndef _CIRCUITELEMENT_H
#define _CIRCUITELEMENT_H

#include "PamolaObject.h"
#include "CircuitTerminal.h"
#include <vector>

class CircuitElement: public PamolaObject {
protected:

	CircuitElement();
	~CircuitElement();
	
private:
	
	std::vector<CircuitTerminal*> terminals;
	
public: 
	
	std::vector<CircuitTerminal*> getTerminals();
	CircuitTerminal* getTerminal(int localId);
	
};

#endif //_CIRCUITELEMENT_H