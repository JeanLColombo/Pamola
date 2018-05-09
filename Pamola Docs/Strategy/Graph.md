# [Pamola](../README.md)
- ## [Strategy](README.md)
  - ### Graph
  
[Ter]: ../../PamolaProject/PamolaProject/CircuitTerminal.h
[Nod]: ../../PamolaProject/PamolaProject/CircuitNode.h
[Ele]: ../../PamolaProject/PamolaProject/CircuitElement.h
[Cir]: ../../PamolaProject/PamolaProject/Circuit.h
[Pam]: ../../PamolaProject/PamolaProject/PamolaObject.h
  
---

## Graph

The implemention of the circuit graph uses polymorphism through the base abstract class [```PamolaObject```][Pam], from this class we create 4 main entities that compose the entireness of the API.
1. **[CircuitElement][Ele]** - Any element that can be put into a circuit, like a resistor, capacitor or any other.
1. **[CircuitTerminal][Ter]** - Represents the *sockects* in a circuit element that are capable of connecting.
1. **[CircuitNode][Nod]** - Store connections between terminals.
1. **[Circuit][Cir]** - Is an assembly of CircuitElement's, CircuitTerminal's and CircuitNode's.

By design it's ensured that connections are:

[CircuitElement][Ele]<->[CircuitTerminal][Ter]<->[CircuitNode][Nod]<->[CircuitTerminal][Ter]<->[CircuitElement][Ele]

As the following visual example:

![Example of entities connection](https://image.ibb.co/jiFfiR/Graph_Example.png)

So a simple circuit may be created like the following:

![Example of circuit assembly connection](https://image.ibb.co/jyRHxm/Circuit_Example.png)
![Example of circuit entities connection](https://image.ibb.co/h0oGOR/Montage_Example.png)
