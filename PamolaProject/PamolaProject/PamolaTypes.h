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

	using varMap = std::map<std::string, std::complex<double>>;
	using eqMap = std::vector<std::function<std::complex<double>(varMap)>>;

	using setterSign = std::function<void(std::complex<double>)>;
	using getterSign = std::function<std::complex<double>(void)>;

	using varEqMap = std::map<std::string, std::tuple<setterSign, getterSign, eqMap>>;
}
