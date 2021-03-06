#pragma once

#include "PamolaObject.h"
#include <complex>
#include <algorithm>

namespace Pamola
{

	class Engine;
	class CircuitNode;
	class CircuitElement;

	class CircuitTerminal : public Object, public std::enable_shared_from_this<CircuitTerminal>
	{

		friend class CircuitElement;
		friend class Engine;
		
	private:

		std::shared_ptr<CircuitNode> node = nullptr;

		const std::weak_ptr<CircuitElement> element;

		std::complex<double> current = 0.0;

		CircuitTerminal(std::weak_ptr<CircuitElement>);
		
	public:

		~CircuitTerminal();

		std::string getVoltageVariable();
		std::string getCurrentVariable();

		const std::shared_ptr<CircuitElement> getElement();

		std::shared_ptr<CircuitNode> getNode();

		std::shared_ptr<CircuitNode> connectTo(std::shared_ptr<CircuitTerminal>);
		std::shared_ptr<CircuitNode> connectTo(std::shared_ptr<CircuitNode>);

		std::complex<double> getCurrent();
		std::complex<double> getVoltage();

		bool setCurrent(std::complex<double>);
		bool disconnect();
		bool isConnected();
		
		varMap getVariables();

		const std::set<uint32_t> getAdjacentComponents();

		Type getPamolaType();

		int getDegreesOfFreedom();

	};
}
