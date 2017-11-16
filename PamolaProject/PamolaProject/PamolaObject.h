/**
 * Project PamolaCore
 */

#pragma once

#include <unordered_map>
#include <vector>
#include "PamolaTypes.h"

class PamolaObject {
protected:

	PamolaObject();

public:

	virtual ~PamolaObject();

private: 

	static std::unordered_map<uint32_t, PamolaObject *> pamolaInstances;

	static uint32_t guid;	

	uint32_t id;

public:

	static const std::unordered_map<uint32_t, PamolaObject *> getPamolaInstances();

	static std::vector<PamolaObject *> getCircuitElements();

	static PamolaObject * getPamolaInstance(uint32_t);

	static void clear();

	uint32_t getId();

	virtual PamolaType getPamolaType() = 0;

	virtual int getDegreesOfFreedom() = 0;
	
};
