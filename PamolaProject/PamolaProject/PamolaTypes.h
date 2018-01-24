#pragma once

#ifndef __GNUC__
#include "stdafx.h"
#endif

namespace Pamola
{
	enum class Type
	{
		CircuitElement,
		CircuitTerminal,
		CircuitNode,
		Circuit,
		Other,
		Error
	};
}
