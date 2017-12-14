#pragma once

#include "Circuit.h"
#include "PamolaTypes.h"
#include "PamolaEngine.h"
#include <set>
#include <vector>
#include <memory>
#include <cassert>
#include <cpplinq.hpp>

class PamolaObject : public std::enable_shared_from_this<PamolaObject> 
{
	// TODO: Check enable_shared_from_thiss usage
	using std::enable_shared_from_this<PamolaObject>::enable_shared_from_this;

private: 

	static uint32_t guid;	

	uint32_t id;

protected:

	PamolaObject();

public:

	virtual ~PamolaObject();

	std::set<uint32_t> getConnectedComponents();
	std::set<uint32_t> getConnectedComponents(std::set<uint32_t>);

public:
	
	uint32_t getId();

	virtual const std::vector<std::shared_ptr<PamolaObject>> getAdjacentComponents() = 0;

	virtual PamolaType getPamolaType() = 0;

	virtual int getDegreesOfFreedom() = 0;
	
};
