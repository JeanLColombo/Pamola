// PamolaConsole.cpp : Defines the entry point for the console application.
//

#ifndef __GNUC__
#include "stdafx.h"
#endif
#include "Learning.h"
#include <iostream>
#include <memory>

void printVector(std::vector<int> vec)
{
	for (auto ele : vec)
		std::cout << ele << " ";

	std::cout << std::endl;
}

class MyClass
{
public:
	MyClass(int a = 12, int b = 6) :A(a), B(b) {};
	~MyClass() {};

	int A;
	int B;
};

int main()
{
	
	printAllPamolas();

	Resistor R1();
	Resistor R1();
	std::cout << "Creating resistor R1.\n" << std::endl;

	printAllPamolas();

	Resistor R2();
	std::cout << "Creating resistor R2.\n" << std::endl;

	printAllPamolas();

	R1.getRight()->connectTo(R2.getLeft());
	std::cout << "Connecting R1 right terminal, to R2 left terminal.\n" << std::endl;

	printAllPamolas();

	std::cout << "Disconnect R1 from R2" << std::endl;
	R1->getRight()->disconnect();

	printAllPamolas();

	std::cout << "Deleting R2" << std::endl;
	delete R2;

	printAllPamolas();
	
	std::cout << "Clear all Pamolas" << std::endl;
	Object::cleanse();

	printAllPamolas();

	return 0;
}
