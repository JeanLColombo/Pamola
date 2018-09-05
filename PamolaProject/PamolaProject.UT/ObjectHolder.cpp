#include "ObjectHolder.h"


namespace Pamola
{
	varMap ObjectHolder::getVariables()
	{
		return {};
	}
	const std::set<uint32_t> ObjectHolder::getAdjacentComponents()
	{
		return {};
	}
	Type ObjectHolder::getPamolaType()
	{
		return Type::Other;
	}
	int ObjectHolder::getDegreesOfFreedom()
	{
		return 0;
	}
}