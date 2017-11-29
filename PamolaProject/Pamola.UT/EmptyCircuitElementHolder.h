#pragma once
#include "..\PamolaProject\CircuitElement.h"
class EmptyCircuitElementHolder : public CircuitElement
{
public:
	EmptyCircuitElementHolder();
	~EmptyCircuitElementHolder();

	int getDegreesOfFreedom();
};

