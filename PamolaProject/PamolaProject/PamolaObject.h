/**
 * Project PamolaCore
 */

#pragma once

#include <unordered_map>

//TODO change les foreaches

class PamolaObject {
protected:

	PamolaObject();
	~PamolaObject();

private: 

	static std::unordered_map<uint32_t, PamolaObject *> pamolaInstances;

	static uint32_t guid;	

	uint32_t id;

public:

	static PamolaObject * getPamolaInstance(uint32_t);

	static void clear();

	uint32_t getId();

	virtual int getDegreesOfFreedom()=0;
	
};