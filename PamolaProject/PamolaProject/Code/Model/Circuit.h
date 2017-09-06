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
	int getElement(int id);
	
	Vector<PamolaObject> getElements();
private: 
	Vector<PamolaObject> pamolas;
};

#endif //_CIRCUIT_H