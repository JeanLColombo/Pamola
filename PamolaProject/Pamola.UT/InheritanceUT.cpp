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
		TEST_METHOD(RawCreationDestruction)
		{
			CircuitElementHolder *obj = new CircuitElementHolder();
			delete obj;
		}
		TEST_METHOD(SmartCreationDestruction)
		{
			std::unique_ptr<CircuitElementHolder> obj(new CircuitElementHolder());
		}
		TEST_METHOD(SmartEmptyCreationDestruction)
		{
			std::unique_ptr<EmptyCircuitElementHolder> obj(new EmptyCircuitElementHolder());
		}
		TEST_METHOD(ScopedCreationDestruction)
		{
			CircuitElementHolder obj{};
		}
		TEST_METHOD(RawEmptyElementCreationDestruction)
		{
			EmptyCircuitElementHolder *obj = new EmptyCircuitElementHolder();
			delete obj;
		}
		TEST_METHOD(ScopedEmptyElementCreationDestruction)
		{
			EmptyCircuitElementHolder obj;
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
		TEST_METHOD(RawConnection)
		{
			CircuitElementHolder *ele1 = new CircuitElementHolder();
			CircuitElementHolder *ele2 = new CircuitElementHolder();

			ele1->getLeft()->connectTo(ele2->getRight());

			delete ele1;
			delete ele2;
		}
	};
}