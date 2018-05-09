#pragma once
#include "..\PamolaProject\PamolaEngine.h"
class PamolaObjectHolder : public Pamola::Object
{
public:
	PamolaObjectHolder();
	~PamolaObjectHolder();

	Pamola::varMap getVariables();

	const std::set<uint32_t> getAdjacentComponents();

	Pamola::Type getPamolaType();

	int getDegreesOfFreedom();
};

