#include "stdafx.h"
#include "CppUnitTest.h"
#include "PamolaObjectHolder.h"
#include "CircuitElementHolder.h"
#include "EmptyCircuitElementHolder.h"
#include <string>
#include <stdio.h>
#include <inttypes.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PamolaUT
{		
	TEST_CLASS(CircuitElementInheritance)
	{
	public:		
		TEST_METHOD(CreationDestruction)
		{
			using namespace Pamola;
			auto obj = createElement<CircuitElementHolder>;
		}
		TEST_METHOD(EmptyCreationDestruction)
		{
			using namespace Pamola;
			auto obj = createElement<EmptyCircuitElementHolder>;
		}
	};

	TEST_CLASS(PamolaObjectInheritance)
	{
		TEST_METHOD(RawCreationDestruction)
		{
			PamolaObjectHolder *obj = new PamolaObjectHolder;
			delete obj;
		}
		TEST_METHOD(ScopedCreationDestruction)
		{
			PamolaObjectHolder obj{};
		}
	};

	TEST_CLASS(Connections)
	{
		TEST_METHOD(Connection1)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			auto ele2 = createElement<CircuitElementHolder>();

			ele1->getLeft()->connectTo(ele2->getRight());
			Assert::AreEqual(2,
				int(ele1->getLeft()->getNode()->getTerminals().size()),
				L"Connection fail - terminals count wrong",
				LINE_INFO());
		}
		TEST_METHOD(Connection2)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			auto ele2 = createElement<CircuitElementHolder>();
			auto ele3 = createElement<CircuitElementHolder>();

			ele1->getLeft()->connectTo(ele2->getRight());
			ele3->getLeft()->connectTo(ele2->getRight()->getNode());
			Assert::AreEqual(3,
				int(ele1->getLeft()->getNode()->getTerminals().size()),
				L"Connection fail - terminals count wrong",
				LINE_INFO());
		}
		TEST_METHOD(Connection3)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			auto ele2 = createElement<CircuitElementHolder>();

			ele1->getLeft()->connectTo(ele2->getRight());
			{
				auto ele3 = createElement<CircuitElementHolder>();
				ele3->getLeft()->connectTo(ele2->getRight()->getNode());
			}
			Assert::AreEqual(2,
				int(ele1->getLeft()->getNode()->getTerminals().size()),
				L"Connection fail - terminals count wrong",
				LINE_INFO());
		}
		TEST_METHOD(Disconnection)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			auto ele2 = createElement<CircuitElementHolder>();

			ele1->getLeft()->connectTo(ele2->getRight());
			ele1->getLeft()->disconnect();
		}
	};

	TEST_CLASS(EngineBehavior)
	{
		TEST_METHOD(MapSize)
		{
			using namespace Pamola;
			int engineSize = Engine::getLocalEngine()->getLocalObjects().size();
			Assert::AreEqual(0,
				engineSize,
				L"Original Engine Size Not 0",
				LINE_INFO());

			auto ele1 = createElement<CircuitElementHolder>();
			engineSize = Engine::getLocalEngine()->getLocalObjects().size();
			Assert::AreEqual(3,
				engineSize,
				L"List of objects' size Not 3",
				LINE_INFO());

			{
				auto ele2 = createElement<CircuitElementHolder>();
				engineSize = Engine::getLocalEngine()->getLocalObjects().size();
				Assert::AreEqual(6,
					engineSize,
					L"List of objects' size Not 6",
					LINE_INFO());

				ele2->getRight()->connectTo(ele1->getLeft());
				engineSize = Engine::getLocalEngine()->getLocalObjects().size();
				Assert::AreEqual(7,
					engineSize,
					L"List of objects' size Not 7",
					LINE_INFO());

				ele2->getRight()->disconnect();
				engineSize = Engine::getLocalEngine()->getLocalObjects().size();
				Assert::AreEqual(6,
					engineSize,
					L"List of objects' size Not 6",
					LINE_INFO());
			}

			engineSize = Engine::getLocalEngine()->getLocalObjects().size();
			Assert::AreEqual(3,
				engineSize,
				L"List of objects' size Not 3",
				LINE_INFO());
		}
		TEST_METHOD(StressEngine)
		{
			using namespace Pamola;
			for (int i = 0; i < 10000; i++)
			{
				auto c = createElement<CircuitElementHolder>();
			}
		}
	};

	TEST_CLASS(PamolaObjectComparators)
	{
		TEST_METHOD(OperatorLT)
		{
			using namespace Pamola;
			std::shared_ptr<Object> ele1 = createElement<CircuitElementHolder>();
			std::shared_ptr<Object> ele2 = createElement<CircuitElementHolder>();
			Assert::AreEqual(ele2 < ele1,
				(ele2->getId() < ele1->getId()),
				L"Operator override fail.",
				LINE_INFO());
		}
		TEST_METHOD(OperatorGT)
		{
			using namespace Pamola;
			std::shared_ptr<Object> ele1 = createElement<CircuitElementHolder>();
			std::shared_ptr<Object> ele2 = createElement<CircuitElementHolder>();
			Assert::AreEqual(ele1 > ele2,
				(ele1->getId() > ele2->getId()),
				L"Operator override fail.",
				LINE_INFO());
		}
		TEST_METHOD(OperatorLTE)
		{
			using namespace Pamola;
			std::shared_ptr<Object> ele1 = createElement<CircuitElementHolder>();
			std::shared_ptr<Object> ele2 = createElement<CircuitElementHolder>();
			Assert::AreEqual(ele1 <= ele2,
				(ele1->getId() <= ele2->getId()),
				L"Operator override fail.",
				LINE_INFO());
		}
		TEST_METHOD(OperatorGTE)
		{
			using namespace Pamola;
			std::shared_ptr<Object> ele1 = createElement<CircuitElementHolder>();
			std::shared_ptr<Object> ele2 = createElement<CircuitElementHolder>();
			Assert::AreEqual(ele1 >= ele2,
				(ele1->getId() >= ele2->getId()),
				L"Operator override fail.",
				LINE_INFO());
		}
		TEST_METHOD(OperatorE)
		{
			using namespace Pamola;
			std::shared_ptr<Object> ele1 = createElement<CircuitElementHolder>();
			std::shared_ptr<Object> ele2 = createElement<CircuitElementHolder>();
			Assert::AreEqual(ele1 == ele2,
				(ele1->getId() == ele2->getId()),
				L"Operator override fail.",
				LINE_INFO());
		}
		TEST_METHOD(OperatorNE)
		{
			using namespace Pamola;
			std::shared_ptr<Object> ele1 = createElement<CircuitElementHolder>();
			std::shared_ptr<Object> ele2 = createElement<CircuitElementHolder>();
			Assert::AreEqual(ele1 != ele2,
				(ele1->getId() != ele2->getId()),
				L"Operator override fail.",
				LINE_INFO());
		}
		TEST_METHOD(StdSetObject)
		{
			using namespace Pamola;
			int length = 100;
			std::vector<std::shared_ptr<CircuitElementHolder>> myVector;
			for (int i = 0; i < length; i++)
			{
				myVector.push_back(createElement<CircuitElementHolder>());
			}
			std::set<std::shared_ptr<Object>> mySet;
			for (int i = 0; i < length; i++)
			{
				mySet.insert(myVector.at(length - i - 1));
			}
			for (int i = 0; i < length; i++)
			{
				Assert::AreEqual((*std::next(mySet.begin(), i))->getId(),
					myVector.at(i)->getId(),
					L"Set is not ordered",
					LINE_INFO());
			}
		}
		TEST_METHOD(StdSetCircuitElement)
		{
			using namespace Pamola;
			int length = 100;
			std::vector<std::shared_ptr<CircuitElementHolder>> myVector;
			for (int i = 0; i < length; i++)
			{
				myVector.push_back(createElement<CircuitElementHolder>());
			}
			std::set<std::shared_ptr<CircuitElement>> mySet;
			for (int i = 0; i < length; i++)
			{
				mySet.insert(myVector.at(length - i - 1));
			}
			for (int i = 0; i < length; i++)
			{
				Assert::AreEqual((*std::next(mySet.begin(), i))->getId(),
					myVector.at(i)->getId(),
					L"Set is not ordered",
					LINE_INFO());
			}
		}
	
	}; 

	TEST_CLASS(CircuitBehavior)
	{
		TEST_METHOD(CreationScoped)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			ele1->getCircuit();
			int engineSize = Engine::getLocalEngine()->getLocalObjects().size();
			Assert::AreEqual(3,
				engineSize,
				L"Circuit behaviour is abnormal - wrong object count",
				LINE_INFO());
		}
		TEST_METHOD(CreationFromElement)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			auto ele2 = createElement<CircuitElementHolder>();
			ele1->getRight()->connectTo(ele2->getRight());
			ele1->getLeft()->connectTo(ele2->getLeft());
			auto cir = ele1->getCircuit();
			int engineSize = Engine::getLocalEngine()->getLocalObjects().size();
			Assert::AreEqual(9,
				engineSize,
				L"Circuit behaviour is abnormal - wrong object count",
				LINE_INFO());
		}
		TEST_METHOD(CreationFromTerminal)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			auto ele2 = createElement<CircuitElementHolder>();
			ele1->getRight()->connectTo(ele2->getRight());
			ele1->getLeft()->connectTo(ele2->getLeft());
			auto cir = ele1->getRight()->getCircuit();
			int engineSize = Engine::getLocalEngine()->getLocalObjects().size();
			Assert::AreEqual(9,
				engineSize,
				L"Circuit behaviour is abnormal - wrong object count",
				LINE_INFO());
		}
		TEST_METHOD(CreationFromNode)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			auto ele2 = createElement<CircuitElementHolder>();
			ele1->getRight()->connectTo(ele2->getRight());
			ele1->getLeft()->connectTo(ele2->getLeft());
			auto cir = ele1->getRight()->getNode()->getCircuit();
			int engineSize = Engine::getLocalEngine()->getLocalObjects().size();
			Assert::AreEqual(9,
				engineSize,
				L"Circuit behaviour is abnormal - wrong object count",
				LINE_INFO());
		}
		TEST_METHOD(TerminalsForFurtherConnections)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			auto ele2 = createElement<CircuitElementHolder>();
			auto cir1 = ele1->getCircuit();
			ele1->getRight()->connectTo(ele2->getRight());
			auto cir2 = ele1->getCircuit();
			ele1->getLeft()->connectTo(ele2->getLeft());
			auto cir3 = ele1->getCircuit();
			Assert::AreEqual(2,
				int(cir1->getTerminals().size()),
				L"Circuit behaviour is abnormal - wrong object count",
				LINE_INFO());
			Assert::AreEqual(2,
				int(cir2->getTerminals().size()),
				L"Circuit behaviour is abnormal - wrong object count",
				LINE_INFO());
			Assert::AreEqual(0,
				int(cir3->getTerminals().size()),
				L"Circuit behaviour is abnormal - wrong object count",
				LINE_INFO());
		}
	};

	TEST_CLASS(EquationSystemGeneration)
	{
		TEST_METHOD(GetVariables)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			auto ele2 = createElement<CircuitElementHolder>();
			ele1->getLeft()->connectTo(ele2->getLeft());
			auto cir = ele1->getCircuit();

			auto variables = cir->getVariables();

			Logger::WriteMessage("Printing Default Variables Values");
			for (auto &var : variables)
			{
				Logger::WriteMessage(std::to_string(var.second().real()).c_str());
			}

			Logger::WriteMessage("Setting Variables:");
			int temp = 1;
			for (auto &var : variables)
			{
				var.first(temp);
				temp += int(var.second().real());
			}

			Logger::WriteMessage("Printing le Fibonacci Variables Values");
			for (auto &var : variables)
			{
				Logger::WriteMessage(std::to_string(var.second().real()).c_str());
			}

			Logger::WriteMessage("Last check");
			Logger::WriteMessage(std::to_string(ele1->getLeft()->getNode()->getVoltage().real()).c_str());
		}
		TEST_METHOD(RealSystemCreation)
		{
			using namespace Pamola;
			auto res = createElement<Resistor>();
			auto vdc = createElement<IdealDCSource>();
			vdc->getPositive()->connectTo(res->getLeft());
			vdc->getNegative()->connectTo(res->getRight());
			auto cir = vdc->getCircuit();
		}
		TEST_METHOD(RealSystemEquationCount)
		{
			using namespace Pamola;
			auto res = createElement<Resistor>();
			auto vdc = createElement<IdealDCSource>();
			vdc->getPositive()->connectTo(res->getLeft());
			vdc->getNegative()->connectTo(res->getRight());
			auto cir = vdc->getCircuit();
			Logger::WriteMessage("Number of Variables in Circuit:");
			Logger::WriteMessage(std::to_string(cir->getVariables().size()).c_str());
			Logger::WriteMessage("Number of Equations in Circuit:");
			Logger::WriteMessage(std::to_string(cir->getEquations().size()).c_str());
		}
		TEST_METHOD(RealSystemEquationEvaluation1)
		{
			using namespace Pamola;
			auto res = createElement<Resistor>();
			auto vdc = createElement<IdealDCSource>();
			vdc->getPositive()->connectTo(res->getLeft());
			vdc->getNegative()->connectTo(res->getRight());
			auto cir = vdc->getCircuit();
			// Set Parameters
			res->setResistance(2.0);
			vdc->setVoltage(10.0);
			// Set Variables
			res->getLeft()->setCurrent(5.0);
			res->getRight()->setCurrent(-5.0);
			vdc->getLeft()->setCurrent(-5.0);
			vdc->getRight()->setCurrent(5.0);
			vdc->getPositive()->getNode()->setVoltage(10.0);
			vdc->getNegative()->getNode()->setVoltage(0.0);
			Logger::WriteMessage("Evaluation 1 [Must be 0]:");
			double out{ 0.0 };
			for (auto &equation : cir->getEquations())
			{
				out += equation().real()*equation().real();
				Logger::WriteMessage(std::to_string(equation().real()).c_str());
			}
			Assert::IsTrue((0.0 == out), L"Equation Output Undefined Behavior", LINE_INFO());
		}
		TEST_METHOD(RealSystemEquationEvaluation2)
		{
			using namespace Pamola;
			auto res = createElement<Resistor>();
			auto vdc = createElement<IdealDCSource>();
			vdc->getPositive()->connectTo(res->getLeft());
			vdc->getNegative()->connectTo(res->getRight());
			auto cir = vdc->getCircuit();
			// Set Parameters
			res->setResistance(2.0);
			vdc->setVoltage(10.0);
			// Set Variables
			res->getLeft()->setCurrent(5.0);
			res->getRight()->setCurrent(-5.0);
			vdc->getLeft()->setCurrent(-5.0);
			vdc->getRight()->setCurrent(5.0);
			vdc->getPositive()->getNode()->setVoltage(24.0);
			vdc->getNegative()->getNode()->setVoltage(14.0);
			Logger::WriteMessage("Evaluation 2 [Must be 0]:");
			double out{ 0.0 };
			for (auto &equation : cir->getEquations())
			{
				out += equation().real()*equation().real();
				Logger::WriteMessage(std::to_string(equation().real()).c_str());
			}
			Assert::IsTrue((0.0 == out), L"Equation Output Undefined Behavior", LINE_INFO());
		}
		TEST_METHOD(RealSystemEquationEvaluation3)
		{
			using namespace Pamola;
			auto res = createElement<Resistor>();
			auto vdc = createElement<IdealDCSource>();
			vdc->getPositive()->connectTo(res->getLeft());
			vdc->getNegative()->connectTo(res->getRight());
			auto cir = vdc->getCircuit();
			// Set Parameters
			res->setResistance(2.0);
			vdc->setVoltage(10.0);
			// Set Variables
			res->getLeft()->setCurrent(5.0);
			res->getRight()->setCurrent(-5.0);
			vdc->getLeft()->setCurrent(-5.0);
			vdc->getRight()->setCurrent(12.0);
			vdc->getPositive()->getNode()->setVoltage(20.0);
			vdc->getNegative()->getNode()->setVoltage(0.0);			
			Logger::WriteMessage("Evaluation 3 [Must NOT be 0]:");
			double out{ 0.0 };
			for (auto &equation : cir->getEquations())
			{
				out += equation().real()*equation().real();
				Logger::WriteMessage(std::to_string(equation().real()).c_str());
			}
			Assert::IsFalse((0.0 == out), L"Equation Output Undefined Behavior", LINE_INFO());
		}
		TEST_METHOD(RealSystemEquationEvaluation4)
		{
			using namespace Pamola;
			auto res = createElement<Resistor>();
			auto vdc = createElement<IdealDCSource>();
			auto gnd = createElement<Ground>();
			vdc->getPositive()->connectTo(res->getLeft());
			vdc->getNegative()->connectTo(res->getRight());
			gnd->getTerminal()->connectTo(vdc->getNegative());
			auto cir = vdc->getCircuit();
			// Set Parameters
			res->setResistance(2.0);
			vdc->setVoltage(10.0);
			// Set Variables
			res->getLeft()->setCurrent(5.0);
			res->getRight()->setCurrent(-5.0);
			vdc->getLeft()->setCurrent(-5.0);
			vdc->getRight()->setCurrent(5.0);
			vdc->getPositive()->getNode()->setVoltage(24.0);
			vdc->getNegative()->getNode()->setVoltage(14.0);
			Logger::WriteMessage("Evaluation 4 [Must NOT be 0]:");
			double out{ 0.0 };
			for (auto &equation : cir->getEquations())
			{
				out += equation().real()*equation().real();
				Logger::WriteMessage(std::to_string(equation().real()).c_str());
			}
			Assert::IsFalse((0.0 == out), L"Equation Output Undefined Behavior", LINE_INFO());
		}
	};

	TEST_CLASS(Dipole)
	{
		TEST_METHOD(OperatorSeries)
		{
			using namespace Pamola;
			auto R1 = createElement<Resistor>();
			auto R2 = createElement<Resistor>();
			auto cir = (R1 + R2)->getCircuit();
			Logger::WriteMessage("List of Circuit Components:");
			std::string component;
			for (auto &element : cir->getElements())
			{
				component = std::to_string(element->getId()) + " = ";
				switch (element->getPamolaType())
				{
				case Pamola::Type::CircuitElement:
					component += "Element";
					break;
				case Pamola::Type::CircuitTerminal:
					component += "Terminal";
					break;
				case Pamola::Type::CircuitNode:
					component += "Node";
					break;
				case Pamola::Type::Circuit:
					component += "Circuit";
					break;
				case Pamola::Type::Other:
					component += "Other";
					break;
				case Pamola::Type::Error:
					component += "Error";
					break;
				default:
					component += "Default";
					break;
				}
				Logger::WriteMessage(component.c_str());
			}
		}
		TEST_METHOD(OperatorParallel)
		{
			using namespace Pamola;
			auto R1 = createElement<Resistor>();
			auto R2 = createElement<Resistor>();
			R1 / R2;
			auto cir = R1->getCircuit();
			Logger::WriteMessage("List of Circuit Components:");
			std::string component;
			for (auto &element : cir->getElements())
			{
				component = std::to_string(element->getId()) + " = ";
				switch (element->getPamolaType())
				{
				case Pamola::Type::CircuitElement:
					component += "Element";
					break;
				case Pamola::Type::CircuitTerminal:
					component += "Terminal";
					break;
				case Pamola::Type::CircuitNode:
					component += "Node";
					break;
				case Pamola::Type::Circuit:
					component += "Circuit";
					break;
				case Pamola::Type::Other:
					component += "Other";
					break;
				case Pamola::Type::Error:
					component += "Error";
					break;
				default:
					component += "Default";
					break;
				}
				Logger::WriteMessage(component.c_str());
			}
		}
		TEST_METHOD(ComplexCircuitCreation)
		{
			using namespace Pamola;
			auto R1 = createElement<Resistor>();
			auto R2 = createElement<Resistor>();
			auto R3 = createElement<Resistor>();
			auto R4 = createElement<Resistor>();
			R1->setResistance(1);
			R2->setResistance(2);
			R3->setResistance(3);
			R4->setResistance(4);
			auto V1 = createElement<IdealDCSource>();
			auto cir = (V1 + R1 / R2 + R3 / R4 + V1)->getCircuit();
			Logger::WriteMessage("List of Circuit Components:");
			std::string component;
			for (auto &element : cir->getElements())
			{
				component = std::to_string(element->getId()) + " = ";
				switch (element->getPamolaType())
				{
				case Pamola::Type::CircuitElement:
					component += "Element";
					break;
				case Pamola::Type::CircuitTerminal:
					component += "Terminal";
					break;
				case Pamola::Type::CircuitNode:
					component += "Node";
					break;
				case Pamola::Type::Circuit:
					component += "Circuit";
					break;
				case Pamola::Type::Other:
					component += "Other";
					break;
				case Pamola::Type::Error:
					component += "Error";
					break;
				default:
					component += "Default";
					break;
				}
				Logger::WriteMessage(component.c_str());
			}
		}
		TEST_METHOD(WheatstoneBridge1)
		{
			using namespace Pamola;
			auto R1 = createElement<Resistor>();
			auto R2 = createElement<Resistor>();
			auto R3 = createElement<Resistor>();
			auto R4 = createElement<Resistor>();
			auto Rb = createElement<Resistor>();
			auto V1 = createElement<IdealDCSource>();
			R1->setResistance(1);
			R2->setResistance(2);
			R3->setResistance(3);
			R4->setResistance(4);
			Rb->setResistance(500);
			V1->setVoltage(12);
			auto cir = (R1 + Rb + R4 + V1 + R1 + R2 + R4 + R3 + R1)->getCircuit();
			Logger::WriteMessage("List of Circuit Components:");
			std::string component;
			for (auto &element : cir->getElements())
			{
				component = std::to_string(element->getId()) + " = ";
				switch (element->getPamolaType())
				{
				case Pamola::Type::CircuitElement:
					component += "Element";
					break;
				case Pamola::Type::CircuitTerminal:
					component += "Terminal";
					break;
				case Pamola::Type::CircuitNode:
					component += "Node";
					break;
				case Pamola::Type::Circuit:
					component += "Circuit";
					break;
				case Pamola::Type::Other:
					component += "Other";
					break;
				case Pamola::Type::Error:
					component += "Error";
					break;
				default:
					component += "Default";
					break;
				}
				Logger::WriteMessage(component.c_str());
			}
		}
		TEST_METHOD(WheatstoneBridge2)
		{
			using namespace Pamola;
			auto R1 = createElement<Resistor>();
			auto R2 = createElement<Resistor>();
			auto R3 = createElement<Resistor>();
			auto R4 = createElement<Resistor>();
			auto Rb = createElement<Resistor>();
			auto V1 = createElement<IdealDCSource>();
			R1->setResistance(1);
			R2->setResistance(2);
			R3->setResistance(15);
			R4->setResistance(30);
			Rb->setResistance(500);
			V1->setVoltage(12);
			auto cir = (R1 + Rb + R4 + V1 + R1 + R2 + R4 + R3 + R1)->getCircuit();
			cir->solve();
			Assert::IsTrue(Rb->getRight()->getCurrent().real() < 1.0e-5);
			Assert::IsTrue(Rb->getRight()->getCurrent().imag() < 1.0e-5);
		}
	};

	TEST_CLASS(ModelSover)
	{
		TEST_METHOD(MockedMS)
		{
			using namespace Pamola;
			auto res = createElement<Resistor>();
			auto vdc = createElement<IdealDCSource>();
			auto gnd = createElement<Ground>();
			vdc->getPositive()->connectTo(res->getLeft());
			vdc->getNegative()->connectTo(res->getRight());
			gnd->getTerminal()->connectTo(vdc->getNegative());
			Engine::getLocalEngine()->setSolver(std::shared_ptr<ModelSolver>(new MockedModelSolver()));
			auto cir = res->getCircuit();
			cir->solve();
			auto mockVolt = vdc->getPositive()->getNode()->getVoltage();
			Assert::IsTrue(mockVolt.real() == 4.0);
			Assert::IsTrue(mockVolt.imag() == 3.0);
		};
	};
}