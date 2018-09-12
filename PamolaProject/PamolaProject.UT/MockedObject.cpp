#include "MockedObject.h"


namespace Pamola
{
	namespace UT
	{
		varMap MockedObject::getVariables()
		{
			return {};
		}
		const std::set<uint32_t> MockedObject::getAdjacentComponents()
		{
			return {};
		}
		Type MockedObject::getPamolaType()
		{
			return Type::Other;
		}
		int MockedObject::getDegreesOfFreedom()
		{
			return 0;
		}
	}
}