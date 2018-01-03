#pragma once
#include "..\PamolaProject\PamolaObject.h"
class PamolaObjectHolder : public Pamola::Object
{
public:
	PamolaObjectHolder();
	~PamolaObjectHolder();

	const std::vector<std::shared_ptr<Pamola::Object>> getAdjacentComponents();

	Pamola::Type getPamolaType();

	int getDegreesOfFreedom();
};

