# [Pamola](../README.md)
 - ## [Using](README.md)
   - ### Connections
   
---
#### Introduction

One of the most important aspects while you are using **Pamola** in order to solve circuit problems is the connection between circuit terminals. This is because the only way a circuit can be meaningful and solvable is when his mesh have connections in such a way that its number of *degrees of freedom* is exactly *zero*. 

A closed mesh is a special case that will ensure the circuit has a defined value for every variable inside it, but there's a misleading when we think that a closed mesh will ensure solvability. On a circuit the normal connections of only basic elements like power supply and resistor will leave a number of *degrees of freedom* of 1. Almost all the times you have a this missing variable is solved using a `Ground` connecting to any point that will be your 0V reference.

#### Coding

Pamola abstrated connections in such a way that it's use is as simple as talking to the program what you want to connect as:

```cpp
int main()
{
  Resistor R1();
  Resistor R2();
  R1.getRight().connectTo(R2.getLeft())
}
```

The `connectTo` method returns a reference to an object that can be used to connect lots of terminals such that:

```cpp
int main()
{
  Resistor R1();
  Resistor R2();
  Resistor R3();
  auto node = R1.getRight().connectTo(R2.getLeft());
  R3.getLeft().connectTo(node);
}
```

In this case, the 3 terminals are connected (R1 right, R2 left, R3 left) this also ensure a chained way to connect, reducing code to express a connection of many terminals: 

```cpp
int main()
{
  Resistor R1();
  Resistor R2();
  Resistor R3();
  Resistor R4();
  R1.getRight().connectTo(R2.getLeft().connectTo(R3.getLeft().connectTo(R4.getRight())));
}
```

You can also connect the node object to another object:

```cpp
int main()
{
  Resistor R1();
  Resistor R2();
  Resistor R3();
  Resistor R4();
  auto nodeA = R1.getLeft().connectTo(R2.getLeft());
  auto nodeB = R3.getRight().connectTo(R4.getRight());
  nodeA.connectTo(nodeB);
}
```

This is specially useful when you want to make mane connections and store separated "assemblies" of connections and make one node of them all.

At last we can create the most simple circuit to underline the simplicity of connections in *Pamola*

```cpp
int main()
{
  Resistor R1();
  DCSource V1();
  Ground G1();
  R1.getLeft().connectTo(V1.getPositive());
  R1.getRight().connectTo(V1.getNegative().connectTo(G1.getTerminal()));
}
```
