#pragma once
#include "..\PamolaProject\PamolaEngine.h"


class CircuitElementHolder : public Pamola::CircuitElement
{
public:
	CircuitElementHolder();
	~CircuitElementHolder();

	std::shared_ptr<Pamola::CircuitTerminal> getLeft();
	std::shared_ptr<Pamola::CircuitTerminal> getRight();

	Pamola::varMap getVariables();

	int getDegreesOfFreedom();
};

