#pragma once
#include "..\PamolaProject\PamolaEngine.h"
#include "..\PamolaProject\PamolaTypes.h"
#include <vector>
#include <map>

namespace Pamola
{
	// Tuples the variable (setter,getter), and its time derivative --> x, x, dx/dt
	using transientVariable = std::tuple<setterSign, getterSign, getterSign>;

}