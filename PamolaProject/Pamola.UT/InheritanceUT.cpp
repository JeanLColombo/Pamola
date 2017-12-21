#include "stdafx.h"
#include "CppUnitTest.h"
#include "PamolaObjectHolder.h"
#include "CircuitElementHolder.h"
#include "EmptyCircuitElementHolder.h"

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
		TEST_METHOD(Connection)
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
		TEST_METHOD(Disconnection)
		{
			using namespace Pamola;
			auto ele1 = createElement<CircuitElementHolder>();
			auto ele2 = createElement<CircuitElementHolder>();

			ele1->getLeft()->connectTo(ele2->getRight());
			ele1->getLeft()->disconnect();
		}
	};
}