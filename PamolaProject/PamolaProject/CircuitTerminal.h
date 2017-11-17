/**
 * Project PamolaCore
 */

#pragma once

#include "CircuitNode.h"
#include "PamolaObject.h"
#include "CircuitElement.h"
#include <complex>

class CircuitNode;

class CircuitTerminal: public PamolaObject , virtual public std::enable_shared_from_this<CircuitTerminal>
{
	friend class CircuitElement;

public:

	CircuitTerminal();
	
public:
	
	~CircuitTerminal();
	
private:

	std::weak_ptr<CircuitElement> element;

	std::shared_ptr<CircuitNode> node = nullptr;

	std::complex<double> current = 0.0;

public: 
	
	std::shared_ptr<CircuitElement> getElement();

	std::shared_ptr<CircuitNode> getNode();

	CircuitNode & connectTo(CircuitTerminal &);
	CircuitNode & connectTo(CircuitNode &);

	std::complex<double> getCurrent();
	std::complex<double> getVoltage();

	bool setCurrent(std::complex<double>);
	bool disconnect();
	bool isConnected();

	const std::vector<std::shared_ptr<PamolaObject>> getAdjacentComponents();

	PamolaType getPamolaType();

	int getDegreesOfFreedom();

};
