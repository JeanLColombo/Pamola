
#include "stdafx.h"
#include "CircuitElement.h"

CircuitElement::CircuitElement(uint32_t numberOfTerminals)
{
	/*const std::shared_ptr<CircuitElement> myElement(this);
	for (uint32_t index = 0; index < numberOfTerminals; index++)
	{
		std::shared_ptr<CircuitTerminal> terminalInstance(new CircuitTerminal(myElement));
		terminals.push_back(std::shared_ptr<CircuitTerminal>(terminalInstance));
	}*/

}

CircuitElement::~CircuitElement()
{
}

const std::vector<std::shared_ptr<CircuitTerminal>> CircuitElement::getTerminals()
{
	return terminals;
}

const std::shared_ptr<CircuitTerminal> CircuitElement::getTerminal(uint32_t localId)
{
	return terminals.at(localId);
}

const std::vector<std::shared_ptr<PamolaObject>> CircuitElement::getAdjacentComponents()
{
	using namespace cpplinq;
	// TODO: Check shared_from_this usage on CircuitTerminal
	auto result =
		from(terminals)
		>> select([](std::shared_ptr<CircuitTerminal> t) {return static_cast<std::shared_ptr<PamolaObject>>(t); })
		>> to_vector();

	return result;
}

PamolaType CircuitElement::getPamolaType()
{
	return PamolaType::CircuitElement;
}

uint32_t CircuitElement::getNumberOfTerminals()
{
	return numberOfterminals;
}
