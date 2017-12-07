#include "stdafx.h"
#include "PamolaObjectHolder.h"

PamolaObjectHolder::PamolaObjectHolder()
{
}

PamolaObjectHolder::~PamolaObjectHolder()
{
}

const std::vector<std::shared_ptr<PamolaObject>> PamolaObjectHolder::getAdjacentComponents()
{
	return { nullptr };
}

PamolaType PamolaObjectHolder::getPamolaType()
{
	return PamolaType::Other;
}

int PamolaObjectHolder::getDegreesOfFreedom()
{
	return 0;
}
