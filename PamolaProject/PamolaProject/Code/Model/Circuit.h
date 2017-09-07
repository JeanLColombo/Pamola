/**
 * Project PamolaCore
 */


#ifndef _CIRCUIT_H
#define _CIRCUIT_H

#include "PamolaObject.h"


class Circuit: public PamolaObject {
public: 
	
	/**
	 * @param id
	 */
	uint32_t getElement(uint32_t id);
	
	Vector<PamolaObject> getElements();
private: 
	Vector<PamolaObject> pamolas;
};

#endif //_CIRCUIT_H