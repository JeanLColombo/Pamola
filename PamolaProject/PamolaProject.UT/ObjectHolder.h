#pragma once
#include "..\PamolaProject\PamolaEngine.h"

namespace Pamola
{
	class ObjectHolder : public Object
	{
	public:
		
		varMap getVariables();

		const std::set<uint32_t> getAdjacentComponents();

		Type getPamolaType();

		int getDegreesOfFreedom();
	};
}