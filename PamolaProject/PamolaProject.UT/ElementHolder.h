#pragma once
#include "..\PamolaProject\PamolaEngine.h"

namespace Pamola
{
	namespace UT
	{
		class ElementHolder : public CircuitElement
		{
		public:
			ElementHolder() : CircuitElement(0) {}
			~ElementHolder() {}
		};
	}
}
