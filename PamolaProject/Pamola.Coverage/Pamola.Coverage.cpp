// Pamola.Coverage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

CircuitElementHolder::CircuitElementHolder()
	: CircuitElement(2)
{
}

CircuitElementHolder::~CircuitElementHolder()
{
}

std::shared_ptr<Pamola::CircuitTerminal> CircuitElementHolder::getLeft()
{
	return getTerminal(0);
}

std::shared_ptr<Pamola::CircuitTerminal> CircuitElementHolder::getRight()
{
	return getTerminal(1);
}

Pamola::varMap CircuitElementHolder::getVariables()
{
	return {};
}

int CircuitElementHolder::getDegreesOfFreedom()
{
	return 2;
}

class EmptyCircuitElementHolder : public Pamola::CircuitElement
{
public:
	EmptyCircuitElementHolder();
	~EmptyCircuitElementHolder();

	Pamola::varMap getVariables();

	int getDegreesOfFreedom();
};

EmptyCircuitElementHolder::EmptyCircuitElementHolder()
{
}

EmptyCircuitElementHolder::~EmptyCircuitElementHolder()
{
}

Pamola::varMap EmptyCircuitElementHolder::getVariables()
{
	return {};
}

int EmptyCircuitElementHolder::getDegreesOfFreedom()
{
	return 0;
}

int main()
{

		{
			using namespace Pamola;
			auto obj = createElement<CircuitElementHolder>;
		}
		{
			using namespace Pamola;
			auto obj = createElement<EmptyCircuitElementHolder>;
		}
	

		{
			using namespace Pamola;

			auto R1 = createElement<Resistor>();
			auto R2 = createElement<Resistor>();
			auto Vcc = createElement<IdealDCSource>();
			auto gnd = createElement<Ground>();

			Vcc->getPositive()->connectTo(R1->getLeft());
			R1->getRight()->connectTo(R2->getLeft());
			R2->getRight()->connectTo(Vcc->getNegative());
			Vcc->getNegative()->connectTo(gnd->getTerminal());

			R1->setResistance(4.0);
			R2->setResistance(6.0);
			Vcc->setVoltage(100.0);

			auto cir = R1->getCircuit();

			cir->solve();

			std::string message1 = "\nVoltages in the System:\n";
			std::string message2 = "\nCurrents in the System:\n";
			for (auto &ele : cir->getElements())
			{
				if (ele->getPamolaType() == Type::CircuitNode)
				{
					message1 += std::to_string(ele->getId()) + "\t\t";
					for (auto &var : ele->getVariables())
					{
						message1 += std::to_string(var.second().real()) + "\t"
							+ std::to_string(var.second().imag()) + "j\n";
					}
				}
				if (ele->getPamolaType() == Type::CircuitTerminal)
				{
					message2 += std::to_string(ele->getId()) + "\t\t";
					for (auto &var : ele->getVariables())
					{
						message2 += std::to_string(var.second().real()) + "\t"
							+ std::to_string(var.second().imag()) + "j\n";
					}
				}
			}



		}

    return 0;
}

