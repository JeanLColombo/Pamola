[//]: # (Documentation Files)
[EleDes]: CircuitElement.md
[ObjDes]: Object.md
[EngDes]: Engine.md
[CirDes]: Circuit.md

[//]: # (Source Files)
[Eng]: ../../PamolaProject/PamolaProject/PamolaEngine.h
[EngCpp]: ../../PamolaProject/PamolaProject/PamolaEngine.cpp
[Obj]: ../../PamolaProject/PamolaProject/PamolaObject.h
[ObjCpp]: ../../PamolaProject/PamolaProject/PamolaObject.cpp
[Cir]: ../../PamolaProject/PamolaProject/Circuit.h   
[Ter]: ../../PamolaProject/PamolaProject/CircuitTerminal.h
[TerCpp]: ../../PamolaProject/PamolaProject/CircuitTerminal.cpp
[Nod]: ../../PamolaProject/PamolaProject/CircuitNode.h
[Ele]: ../../PamolaProject/PamolaProject/CircuitElement.h

# [Pamola](../README.md)
- ## [Class Descriptions](README.md)

  - ### [Pamola::Object][ObjDes]

#### Files

- [Header file][Obj];
- [Cpp file][ObjCpp].

#### Responsabilities

The Pamola [Object][ObjDes] class responsabilities are:
- The [Object][ObjDes] class is the parentmost abstrac class of any Pamola graph node;
- Holds the identifier (Id), handled by the [Engine][EngDes] during their creation, ensuring a Multiton pattern;
- Allows acquisition of a [Circuit][CirDes] class instance based on its connected [Object][ObjDes]'s instances;
- Allows acquisition of equations describing the behavior of [Pamo]



All classes deriving from [Object][ObjDes] are created by an [Engine][EngDes] class instance;

 
