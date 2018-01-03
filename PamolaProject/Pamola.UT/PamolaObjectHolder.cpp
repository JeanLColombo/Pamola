#include "stdafx.h"
#include "PamolaObjectHolder.h"

PamolaObjectHolder::PamolaObjectHolder()
{
}

PamolaObjectHolder::~PamolaObjectHolder()
{
}

const std::vector<std::shared_ptr<Pamola::Object>> PamolaObjectHolder::getAdjacentComponents()
{
	return { nullptr };
}

Pamola::Type PamolaObjectHolder::getPamolaType()
{
	return Pamola::Type::Other;
}

int PamolaObjectHolder::getDegreesOfFreedom()
{
	return 0;
}
