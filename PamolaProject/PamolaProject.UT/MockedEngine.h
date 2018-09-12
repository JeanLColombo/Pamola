#pragma once
#include "..\PamolaProject\PamolaEngine.h"

namespace Pamola
{
	namespace UT
	{
		class MockedEngine : public Engine
		{
		public:
			MockedEngine() : Engine(0) {}
			~MockedEngine() {}
		};
	}
}
