/**
 * Project PamolaCore
 */


#ifndef _PAMOLAOBJECT_H
#define _PAMOLAOBJECT_H

#include <unordered_map>

class PamolaObject {
protected:

	PamolaObject();
	~PamolaObject();

private: 

	uint32_t id;

	static uint32_t guid;
	static std::unordered_map<uint32_t, PamolaObject *> pamolaInstances;

public:

	uint32_t getId();

	static PamolaObject* getPamolaInstance(uint32_t);

	virtual int getDegreesOfFreedom()=0;
	
};

#endif //_PAMOLAOBJECT_H