#pragma once
#include <vector>
#include <functional>

namespace SystemSolver
{
	using oneVarFunc = std::function<double(double)>;
	using multVarFunc = std::function<double(const std::vector<double> &)>;

	using matrix = std::vector<std::vector<double>>;
}