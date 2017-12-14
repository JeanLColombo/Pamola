#pragma once
#include "PamolaObject.h"
#include <memory>
#include <set>

class PamolaEngine
{

	friend class PamolaObject;

private:

	static const std::shared_ptr<PamolaEngine> localEngine;

	std::set<PamolaObject*> localObjects;

protected:

	PamolaEngine();

public:

	~PamolaEngine();

	static const std::shared_ptr<PamolaEngine> getLocalEngine();

	const std::set<PamolaObject*> getLocalObjects();
};

