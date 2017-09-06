/**
 * Project PamolaCore
 */


#ifndef _CIRCUITELEMENT_H
#define _CIRCUITELEMENT_H

#include "PamolaObject.h"


class CircuitElement: public PamolaObject {
public: 
	
	CircuitTerminal getTerminals();
	
	/**
	 * @param terminal
	 */
	void setTerminals(CircuitTerminal terminal);
private: 
	Vector<CircuitTerminal> terminals;
};

#endif //_CIRCUITELEMENT_H