#pragma once
#include "..\PamolaProject\PamolaEngine.h"

namespace Pamola
{
	namespace UT
	{
		class MockedEngine : public Engine
		{
		public:
			MockedEngine(int startGuid = 0) : Engine(startGuid) {}
			~MockedEngine() {}
		};
	}
}
