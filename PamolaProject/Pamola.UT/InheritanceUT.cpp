#include "stdafx.h"
#include "CppUnitTest.h"
#include "PamolaObjectHolder.h"
#include "CircuitElementHolder.h"
#include "EmptyCircuitElementHolder.h"
#include <iostream>

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
	};
}