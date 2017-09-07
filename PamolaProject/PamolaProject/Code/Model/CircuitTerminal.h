/**
 * Project PamolaCore
 */


#ifndef _CIRCUITTERMINAL_H
#define _CIRCUITTERMINAL_H

#include "PamolaObject.h"
#include "CircuitElement.h"


class CircuitTerminal: public PamolaObject {
protected:
	CircuitTerminal();
	~CircuitTerminal();

public: 
	
	CircuitElement* getElement();
	
		
	double getCurrent();
	
	/**
	 * @param current
	 */
	void setCurrent(double current);
	
	/**
	 * @param terminal
	 */
	bool connectTo(CircuitTerminal* terminal);
	
	/**
	 * @param node
	 */
	//bool connectTo(CircuitNode node);
	
	double getVoltage();
private: 
	CircuitElement element;
	double current;
};

#endif //_CIRCUITTERMINAL_H