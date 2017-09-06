/**
 * Project PamolaCore
 */


#ifndef _CIRCUITNODE_H
#define _CIRCUITNODE_H

#include "PamolaObject.h"


class CircuitNode: public PamolaObject {
public: 
	
	CircuitTerminal getTerminals();
	
	/**
	 * @param terminal
	 */
	void setTerminals(CircuitTerminal terminal);
	
	double getVoltage();
	
	/**
	 * @param voltage
	 */
	void setVoltage(double voltage);
private: 
	Vector<CircuitTerminal> terminals;
	double voltage;
};

#endif //_CIRCUITNODE_H