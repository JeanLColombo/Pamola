/**
 * Project PamolaCore
 */


#ifndef _PAMOLAOBJECT_H
#define _PAMOLAOBJECT_H

class PamolaObject {
public: 
	
	int getId();
	
	static object getPamolaInstances();
protected: 
	
	void PamolaObject();
private: 
	int id;
	static object pamolaInstances;
};

#endif //_PAMOLAOBJECT_H