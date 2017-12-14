#pragma once
#include <memory>
#include <vector>
#include "PamolaObject.h"

class PamolaEngine
{

	friend PamolaObject;

private:

	static const std::shared_ptr<PamolaEngine> localEngine;

	std::vector<PamolaObject*> localObjects;

protected:

	PamolaEngine();

public:

	~PamolaEngine();

	static const std::shared_ptr<PamolaEngine> getLocalEngine();

	const std::vector<PamolaObject*> getLocalObjects();
};

