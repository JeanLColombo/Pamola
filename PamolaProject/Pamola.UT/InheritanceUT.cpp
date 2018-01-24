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
}