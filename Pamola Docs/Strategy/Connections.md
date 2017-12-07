# [Pamola](../README.md)
- ## [Strategy](README.md)

  - ### <a name="StrCon">Connections

[Ter]: ../../PamolaProject/PamolaProject/CircuitTerminal.h
[Nod]: ../../PamolaProject/PamolaProject/CircuitNode.h
[Ele]: ../../PamolaProject/PamolaProject/CircuitElement.h

---
#### Introduction

In Pamola, the element-to-element connections are modeled using a three-part methodology:
- Terminal-to-teminal (TT);
- Terminal-to-node (TN);
- Node-to-node (NN).

This connections are handled by the [CircuitTerminal][Ter] and [CircuitNode][Nod] classes. To understand how these connections are handled, the relationships between [CircuitTerminal][Ter] and [CircuitElement][Ele], and [CircuitTerminal][Ter] and [CircuitNode][Nod] must be futher analysed.  

#### [CircuitTerminal][Ter] relationships

##### [CircuitElement][Ele] class

[CircuitElement][Ele] and [CircuitTerminal][Ter] have a owner relationship, in which [CircuitTerminal][Ter] is owned by [CircuitElement][Ele]. This dictates some behaviors:
- The element object is responsible for creating/destroying its terminal objects;
- The terminal objects know they belong to an element object, and thus know its existance;
- The element object knows it has terminal objects, and thus knows their existances.

The terminals are stored in the [CircuitElement][Ele] class via a ```std::vector``` container:

```cpp
std::vector<CircuitTerminal> terminals;
```

This automaticaly ensures the [CircuitTerminal][Ter] destructor is called when the element object is destroyed.

The terminal object creation is handled by the ```createTerminals()``` method, belonging to [CircuitElement][Ele], which creates *n* terminal objects belonging to the element object:

Since [CircuitElement][Ele] is a virtual class, a new user defined element class must inherit it to be able to be properly use ```createTerminals()```. The inheritance procedure, alongside the appropriate usege of ```createTerminals()``` are described in [Extending](Extending/README.md).


---
