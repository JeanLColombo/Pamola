#pragma once

#include "Circuit.h"
#include "PamolaTypes.h"
#include <set>
#include <vector>
#include <memory>
#include <cassert>
#include <cpplinq.hpp>
#include <unordered_map>


//class Circuit;

class PamolaObject : public std::enable_shared_from_this<PamolaObject> 
{
	// TODO: Check enable_shared_from_thiss usage
	using std::enable_shared_from_this<PamolaObject>::enable_shared_from_this;

protected:

	PamolaObject();

public:

	virtual ~PamolaObject();

private: 

	//static std::unordered_map<uint32_t, std::weak_ptr<PamolaObject>> pamolaInstances;

	static std::unordered_map<uint32_t, PamolaObject*> pamolaInstances;

	static uint32_t guid;	

	uint32_t id;

	std::set<uint32_t> getConnectedComponents();
	std::set<uint32_t> getConnectedComponents(std::set<uint32_t>);

public:

	//static const std::unordered_map<uint32_t, std::weak_ptr<PamolaObject>> & getPamolaInstances();
	
	static const std::unordered_map<uint32_t, PamolaObject*> & getPamolaInstances();

	//static std::weak_ptr<PamolaObject> getPamolaInstance(uint32_t);

	static PamolaObject* getPamolaInstance(uint32_t);

	//std::shared_ptr<Circuit> getCircuit();

	uint32_t getId();

	virtual const std::vector<std::shared_ptr<PamolaObject>> getAdjacentComponents() = 0;

	virtual PamolaType getPamolaType() = 0;

	virtual int getDegreesOfFreedom() = 0;
	
};
