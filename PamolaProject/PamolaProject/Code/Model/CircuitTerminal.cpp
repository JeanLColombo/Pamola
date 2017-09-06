/**
 * Project PamolaCore
 */


#include "CircuitTerminal.h"

/**
 * CircuitTerminal implementation
 */


/**
 * @return CircuitElement
 */
CircuitElement CircuitTerminal::getElement() {
    return null;
}

/**
 * @param element
 */
void CircuitTerminal::setElement(CircuitElement element) {

}

/**
 * @return double
 */
double CircuitTerminal::getCurrent() {
    return 0.0;
}

/**
 * @param current
 */
void CircuitTerminal::setCurrent(double current) {

}

/**
 * @param terminal
 * @return bool
 */
bool CircuitTerminal::connectTo(CircuitTerminal terminal) {
    return false;
}

/**
 * @param node
 * @return bool
 */
bool CircuitTerminal::connectTo(CircuitNode node) {
    return false;
}

/**
 * @return double
 */
double CircuitTerminal::getVoltage() {
    return 0.0;
}