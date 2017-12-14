#include "stdafx.h"
#include "PamolaEngine.h"

const std::shared_ptr<PamolaEngine> PamolaEngine::localEngine(new PamolaEngine());

PamolaEngine::PamolaEngine()
{
}

PamolaEngine::~PamolaEngine()
{
}

const std::shared_ptr<PamolaEngine> PamolaEngine::getLocalEngine()
{
	return localEngine;
}

const std::set<PamolaObject*> PamolaEngine::getLocalObjects()
{
	return localObjects;
}
