#pragma once
#include "..\PamolaProject\PamolaObject.h"
class PamolaObjectHolder : public PamolaObject
{
public:
	PamolaObjectHolder();
	~PamolaObjectHolder();

	const std::vector<std::shared_ptr<PamolaObject>> getAdjacentComponents();

	PamolaType getPamolaType();

	int getDegreesOfFreedom();
};

