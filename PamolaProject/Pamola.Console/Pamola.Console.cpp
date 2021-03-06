// Pamola.Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\PamolaProject\PamolaEngine.h"
#include <iostream>

void printMolas(std::shared_ptr<Pamola::Circuit> &cir) 
{
	std::cout << "All Variables:" << std::endl;

	for (auto &pair : cir->getVariables())
	{
		std::cout << pair.second() << std::endl;
	}
};

int main()
{
	using namespace Pamola;

	auto R1 = Engine::getLocalEngine()->createElement<Resistor>();
	auto R2 = Engine::getLocalEngine()->createElement<Resistor>();
	auto R3 = Engine::getLocalEngine()->createElement<Resistor>();
	auto Vcc = Engine::getLocalEngine()->createElement<IdealDCSource>();
	auto gnd = Engine::getLocalEngine()->createElement<Ground>();

	R1->setResistance(5.0);
	R2->setResistance(5.0);
	R3->setResistance(10.0);

	Vcc->setVoltage(5.0);

	auto cir = (R1 + R2 + R3 + Vcc + R1)->getCircuit();
	Vcc->getRight()->connectTo(gnd->getTerminal());

	cir->solve();

	printMolas(cir);

    return 0;
}

