#pragma once
#include "..\PamolaProject\CircuitElement.h"

class EmptyCircuitElementHolder : public Pamola::CircuitElement
{
public:
	EmptyCircuitElementHolder();
	~EmptyCircuitElementHolder();

	int getDegreesOfFreedom();
};