#pragma once

#include "PamolaObject.h"
#include <vector>
#include <complex>

namespace Pamola
{
	class Engine;
	class CircuitTerminal;

	class CircuitNode : public Object, public std::enable_shared_from_this<CircuitNode>
	{
		using std::enable_shared_from_this<CircuitNode>::shared_from_this;

		friend class Engine;
		friend class CircuitTerminal;

	private:

		std::vector<std::weak_ptr<CircuitTerminal>> terminals;

		std::complex<double> voltage;

		CircuitNode();

	public:

		~CircuitNode();

	public:

		std::shared_ptr<CircuitNode> connectTo(std::shared_ptr<CircuitNode>);

		const std::vector<std::shared_ptr<CircuitTerminal>> getTerminals();

		std::complex<double> getVoltage();

		bool setVoltage(std::complex<double>);

		std::set<std::string> getVariables();

		const std::set<uint32_t> getAdjacentComponents();

		Type getPamolaType();

		int getDegreesOfFreedom();

	};
}