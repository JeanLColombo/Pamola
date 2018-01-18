#pragma once
#include "..\PamolaProject\PamolaEngine.h"
class PamolaObjectHolder : public Pamola::Object
{
public:
	PamolaObjectHolder();
	~PamolaObjectHolder();

	const std::set<uint32_t> getAdjacentComponents();

	Pamola::Type getPamolaType();

	int getDegreesOfFreedom();
};

