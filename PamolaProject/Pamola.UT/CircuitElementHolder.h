#pragma once
#include "..\PamolaProject\CircuitElement.h"


class CircuitElementHolder : public Pamola::CircuitElement
{
public:
	CircuitElementHolder();
	~CircuitElementHolder();

	std::shared_ptr<Pamola::CircuitTerminal> getLeft();
	std::shared_ptr<Pamola::CircuitTerminal> getRight();

	int getDegreesOfFreedom();
};

