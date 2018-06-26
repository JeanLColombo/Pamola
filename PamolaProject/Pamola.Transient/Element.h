#pragma once
#include "..\PamolaProject\CircuitElement.h"
#include "Types.h"


namespace Pamola
{
	class TransientElement : public Pamola::CircuitElement
	{
	public:
		virtual ~TransientElement();

		virtual std::vector<transientVariable> getTransientVariables() = 0;
	};
}