#pragma once
#include <vector>
#include <functional>
#include <Eigen/Dense>

namespace SystemSolver
{
	using oneVarFunc = std::function<double(double)>;
	using multVarFunc = std::function<double(const std::vector<double> &)>;

}