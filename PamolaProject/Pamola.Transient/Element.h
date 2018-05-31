#pragma once
#include "..\PamolaProject\CircuitElement.h"
#include "Types.h"


namespace Pamola
{
	namespace Transient
	{
		class Element : public Pamola::CircuitElement
		{
		public:
			virtual ~Element();

			virtual std::vector<transientVariable> getTransientVariables() = 0;
		};
	}
}