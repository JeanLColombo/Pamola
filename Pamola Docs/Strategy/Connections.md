# [Pamola](../README.md)
- ## [Strategy](README.md)

  - ### <a name="StrCon">Connections

[Ter]: ../../PamolaProject/PamolaProject/CircuitTerminal.h
[TerCpp]: ../../PamolaProject/PamolaProject/CircuitTerminal.cpp
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
#include <vector>

std::vector<CircuitTerminal> terminals;
```

This automaticaly ensures the [CircuitTerminal][Ter] destructor is called when the element object is destroyed.

The terminal object creation is handled by the ```createTerminals()``` method, belonging to [CircuitElement][Ele], which creates *n* terminal objects belonging to the element object:

```cpp
bool CircuitElement::createTerminals(uint32_t numberOfTerminals)
{
	if (numberOfTerminals > 0)
	{
		for (uint32_t i = 0; i < numberOfTerminals; i++)
		{
			//std::shared_ptr<CircuitTerminal> terminalInstance{ new CircuitTerminal(this) };
			auto terminalInstance = std::make_shared<CircuitTerminal>(this);
			terminals.push_back(terminalInstance);
		}			
		
		return true;
	}	
	return false;
}
```

Since [CircuitElement][Ele] is a virtual class, a new user defined element class must inherit it to be able to be properly use ```createTerminals()```. The inheritance procedure, alongside the appropriate usege of ```createTerminals()``` are described in [Extending](../Extending/README.md).

##### [CircuitNode][Nod] class

[CircuitTerminal][Ter] and [CircuitNode][Nod] classes have an aggregation-like relationship, in which the terminal object can either have a node object or not. It's aggregation-like because the [CircuitTerminal][Ter] class is responsible for creating/destroying the node object, whereas the terminal object is not necessarily responsible for creating/destroying the node objects. The following characteristics dictates this relationship:
- The [CircuitTerminal][Ter] class is responsible for handling creation/destruction of node objects;
- A terminal object has a aggregation relationship with the node object. Multiple terminal objects can have the same node object;
- A terminal can either have no node objects (disconnected), or a single node object (connected). This ownership is modeled throught a ```shared_ptr```;
- If it has a node object, the terminal object knows it has it, and thus knows its existance;
- A node object can belong to at least two terminal objects. This ownership is modeled through a ```std::vector``` container of ```weak_ptr```'s;
- The node object knows it belongs to its terminal objects, and thus knows their existances; 
- When a terminal object detects the presence of a node object belonging to only one terminal object, it issues the node object's destruction;
- Because node objects are accessed throuht ```shared_ptr```'s, when no other terminal objects point to them, their count reference is set to *0*, and the node objects are automatically destroyed, avoiding leaks.  

In the [CircuitTerminal][Ter] class, the node object's address is stored as a member with a ```nullptr``` default value:

```cpp
#include <memory>

std::shared_ptr<CircuitNode> node = nullptr;
```

In the [CircuitNode][Nod] class, the terminal objects's addresses are stored in a container, with no default values:

```cpp
#include <vector>
#include <memory>

std::vector<std::weak_ptr<CircuitTerminal>> terminals;
```
The construction/destruction of node objects is issued by connecting and disconnecting terminals, through the [CircuitTerminal][Ter]'s methods [```connectTo()```][TerCpp] and [```disconnect()```][TerCpp]. The proper usage of these methods is explained in [Using](../Using/Connections.md), though the following example ilustrates this process:

---

***Example:*** 

Consider two terminal objects, **T1** and **T2**, disconnected. The user calls ```T1.connectTo(T2)```. Since both are disconnected, **T1** creates a new node object **N**, and stores its reference. **T1** and **T2** then connect to **N**, making **T2** store a reference to **N**, while **N** stores weak references to **T1** and **T2**.

Later, the user calls ```T1.disconnect()```. This causes **T1** to loose the reference to **N**. Since the terminal reference in **N** is set to *1*, ```T1.disconnect()``` calls ```T2.disconnect()```. This causes **T2** to loose the reference to terminal **N**. Since no more terminals reference node **N**, and since this was issued by a method in terminal **T2**, this leads to **T2** destroying **N**, even though **N** was not created by it.  

---

Something here

---
