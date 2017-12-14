#pragma once
#include "..\PamolaProject\CircuitElement.h"

class CircuitElementHolder : public CircuitElement
{
public:
	CircuitElementHolder();
	~CircuitElementHolder();

	std::shared_ptr<CircuitTerminal> getLeft();
	std::shared_ptr<CircuitTerminal> getRight();

	int getDegreesOfFreedom();
};

