#pragma once
#include "..\PamolaProject\PamolaEngine.h"

class EmptyCircuitElementHolder : public Pamola::CircuitElement
{
public:
	EmptyCircuitElementHolder();
	~EmptyCircuitElementHolder();

	int getDegreesOfFreedom();
};