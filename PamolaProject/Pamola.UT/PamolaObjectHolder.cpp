#include "stdafx.h"
#include "PamolaObjectHolder.h"

PamolaObjectHolder::PamolaObjectHolder()
{
}

PamolaObjectHolder::~PamolaObjectHolder()
{
}

const std::set<uint32_t> PamolaObjectHolder::getAdjacentComponents()
{
	return std::set<uint32_t>();
}

Pamola::Type PamolaObjectHolder::getPamolaType()
{
	return Pamola::Type::Other;
}

int PamolaObjectHolder::getDegreesOfFreedom()
{
	return 0;
}
