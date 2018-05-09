#pragma once

#ifndef __GNUC__
#include "stdafx.h"
#endif

#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <complex>
#include <functional>

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
		
	using setterSign = std::function<void(std::complex<double>)>;
	using getterSign = std::function<std::complex<double>(void)>;

	using ourTuple = std::pair<setterSign, getterSign>;
	using varMap = std::vector<ourTuple>;
	using eqMap = std::vector<getterSign>;
	
}
