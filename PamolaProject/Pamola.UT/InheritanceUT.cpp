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
		TEST_METHOD(ScopedCreationDestruction)
		{
			CircuitElementHolder obj{};
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
}