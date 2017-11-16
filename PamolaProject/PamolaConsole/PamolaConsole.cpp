// PamolaConsole.cpp : Defines the entry point for the console application.
//

#ifndef __GNUC__
#include "stdafx.h"
#endif
#include "Learning.h"

int main()
{
	
	printAllPamolas();

	Resistor *R1 = new Resistor;
	std::cout << "Creating resistor R1.\n" << std::endl;

	printAllPamolas();

	Resistor *R2 = new Resistor;
	std::cout << "Creating resistor R2.\n" << std::endl;

	printAllPamolas();

	R1->getRight()->connectTo(R2->getLeft());
	std::cout << "Connecting R1 right terminal, to R2 left terminal.\n" << std::endl;

	printAllPamolas();

	std::cout << "Deleting R2" << std::endl;
	delete R2;

	printAllPamolas();
	
	std::cout << "Clear all Pamolas" << std::endl;
	PamolaObject::clear();

	printAllPamolas();

	return 0;
}
