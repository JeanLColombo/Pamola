/**
 * Project PamolaCore
 */

#pragma once

#include <unordered_map>
#include <cpplinq.hpp>
#include <vector>
#include "PamolaTypes.h"
#include "Circuit.h"
#include <set>

class Circuit;

class PamolaObject {
protected:

	PamolaObject();

public:

	virtual ~PamolaObject();

private: 

	static std::unordered_map<uint32_t, PamolaObject *> pamolaInstances;

	static uint32_t guid;	

	uint32_t id;

	std::set<uint32_t> getConnectedComponents();
	std::set<uint32_t> getConnectedComponents(std::set<uint32_t>);

public:

	static const std::unordered_map<uint32_t, PamolaObject *> getPamolaInstances();

	static std::vector<PamolaObject *> getCircuitElements();

	static std::set<PamolaObject*> 

	static PamolaObject * getPamolaInstance(uint32_t);

	static void clear();

	Circuit* getCircuit();

	uint32_t getId();

	virtual std::vector<PamolaObject*> getAdjacentComponents() = 0;

	virtual PamolaType getPamolaType() = 0;

	virtual int getDegreesOfFreedom() = 0;
	
};