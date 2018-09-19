#pragma once
#include "..\PamolaProject\PamolaEngine.h"

namespace Pamola
{
	namespace UT
	{
		class MockedObject : public Object
		{
		public:

			varMap getVariables() { return {}; }

			const std::set<uint32_t> getAdjacentComponents() { return {}; }

			Type getPamolaType() { return Type::Error; }

			Type getBasePamolaType() { return Object::getPamolaType(); }
		};
	}
}