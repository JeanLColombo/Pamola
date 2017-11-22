# Pamola

  Aimed to solve complex circuits, **Pamola** is an API written in C++ that abstracts all aspects of numerical solving and circuit creation with a simple syntax. Our main focus is a steady state RLC solver, but we plan to implement transient and signal handling.

## Graph

  The implemention of the circuit graph uses polymorphism through the base abstract class ```PamolaObject```, from this class we create 4 main entities that compose the entireness of the API.
  1. **CircuitElement** - Any element that can be put into a circuit, like a resistor, capacitor or any other.
  1. **CircuitTerminal** - Represents the *sockects* in a circuit element that are capable of connecting.
  1. **CircuitNode** - Store connections between terminals.
  1. **Circuit** - Is an assembly of CircuitElement's, CircuitTerminal's and CircuitNode's.
  
  By design it's ensured that connections are:
  
    CircuitElement<->CircuitTerminal<->CircuitNode<->CircuitTerminal<->CircuitElement
  
  As the following visual example:
  
  ![Example of entities connection](https://image.ibb.co/jiFfiR/Graph_Example.png)
  
  So a simple circuit may be created like the following:
  
  ![Example of circuit assembly connection](https://image.ibb.co/jyRHxm/Circuit_Example.png)
  ![Example of circuit entities connection](https://image.ibb.co/h0oGOR/Montage_Example.png)
