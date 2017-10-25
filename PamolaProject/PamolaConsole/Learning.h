
#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "CircuitNode.h"
#include <cpplinq.hpp>

class Learning
{
public:
	Learning();
	~Learning();
};

class foo;

class bar;

int main1();

int main2();

class Resistor : public CircuitElement {

public:

	Resistor();
	~Resistor();

	CircuitTerminal * getLeft();
	CircuitTerminal * getRight();

	int getDegreesOfFreedom();

};

void printAllPamolas();

std::string printPamola(PamolaObject *);

std::string printPamola(CircuitElement *);

std::string printPamola(CircuitTerminal *);

std::string printPamola(CircuitNode *);
