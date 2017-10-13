// PamolaConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Learning.h"

int main()
{
	
	printAllPamolas();

	Resistor R1;
	std::cout << "Creating resistor R1.\n" << std::endl;

	printAllPamolas();

	Resistor R2;
	std::cout << "Creating resistor R1.\n" << std::endl;

	printAllPamolas();

	R1.getRight()->connectTo(R2.getLeft());
	std::cout << "Connecting R1 right terminal, to R2 left terminal.\n" << std::endl;

	printAllPamolas();

	PamolaObject::clear();
	return 0;
}
