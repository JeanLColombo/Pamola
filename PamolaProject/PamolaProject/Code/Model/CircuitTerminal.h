/**
 * Project PamolaCore
 */


#ifndef _CIRCUITTERMINAL_H
#define _CIRCUITTERMINAL_H

#include "PamolaObject.h"


class CircuitTerminal: public PamolaObject {
public: 
	
	CircuitElement getElement();
	
	/**
	 * @param element
	 */
	void setElement(CircuitElement element);
	
	double getCurrent();
	
	/**
	 * @param current
	 */
	void setCurrent(double current);
	
	/**
	 * @param terminal
	 */
	bool connectTo(CircuitTerminal terminal);
	
	/**
	 * @param node
	 */
	bool connectTo(CircuitNode node);
	
	double getVoltage();
private: 
	CircuitElement element;
	double current;
};

#endif //_CIRCUITTERMINAL_H