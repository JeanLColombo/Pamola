#pragma once

#include "CircuitNode.h"
#include "PamolaObject.h"
#include "CircuitElement.h"
#include <complex>

class CircuitTerminal: public PamolaObject , public std::enable_shared_from_this<CircuitTerminal>
{

	friend class CircuitElement;

public:

	using std::enable_shared_from_this<CircuitTerminal>::shared_from_this;
	
private:
	
	std::shared_ptr<CircuitNode> node = nullptr;

	const std::weak_ptr<CircuitElement> element;

	std::complex<double> current = 0.0;

private:

	CircuitTerminal(std::weak_ptr<CircuitElement>);

public:

	~CircuitTerminal();

public: 
	
	const std::shared_ptr<CircuitElement> getElement();

	std::shared_ptr<CircuitNode> getNode();

	std::shared_ptr<CircuitNode> connectTo(std::shared_ptr<CircuitTerminal>);
	std::shared_ptr<CircuitNode> connectTo(std::shared_ptr<CircuitNode>);

	std::complex<double> getCurrent();
	std::complex<double> getVoltage();

	bool setCurrent(std::complex<double>);
	bool disconnect();
	bool isConnected();

	const std::vector<std::shared_ptr<PamolaObject>> getAdjacentComponents();

	PamolaType getPamolaType();

	int getDegreesOfFreedom();

};
