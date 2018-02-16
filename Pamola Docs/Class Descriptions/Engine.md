[EleDes]: CircuitElement.md
[ObjDes]: Object.md
[EngDes]: Engine.md

[Eng]: ../../PamolaProject/PamolaProject/PamolaEngine.h
[EngCpp]: ../../PamolaProject/PamolaProject/PamolaEngine.cpp
[Obj]: ../../PamolaProject/PamolaProject/PamolaObject.h
[Cir]: ../../PamolaProject/PamolaProject/Circuit.h   
[Ter]: ../../PamolaProject/PamolaProject/CircuitTerminal.h
[TerCpp]: ../../PamolaProject/PamolaProject/CircuitTerminal.cpp
[Nod]: ../../PamolaProject/PamolaProject/CircuitNode.h
[Ele]: ../../PamolaProject/PamolaProject/CircuitElement.h

# [Pamola](../README.md)
- ## [Class Descriptions](README.md)

  - ### [Pamola::Engine][EngDes]

#### Files

- [Header file][Eng];
- [Cpp file][EngCpp].

#### Responsabilities

The Pamola [Engine][EngDes] class responsibilities are:
- Creating/maintaining all classes deriving from Pamola [Object][ObjDes] class;
- Supplying access to all classes deriving from [Object][ObjDes] class;
- Handling all includes into ``<PamolaEngine.h>`` header.

#### Object Creation

Once the program is loaded, a ``static`` [Engine][EngDes]  instance is created. This is made in order to allow the user better freedom in creating their own Pamola [Circuit Element][EleDes] instances. For the time being, this will be the [Engine][EngDes] default behaviour, and thus its constructor is kept ``protected``. Further improvements will focus on removing all static allocation and allowing multiple [Engine][EngDes] instances.

#### Memory Handling

All memory is handled dynamically through ``std::shared_ptr`` and ``std::weak_ptr``, in order to avoid leaks and preserve lifetime safety.

#### Members and Methods

##### Public Methods

| Name                                 | Return Type                                     | Description                                                                                      |
|--------------------------------------|-------------------------------------------------|--------------------------------------------------------------------------------------------------|
| ``~Engine()``                        | ``void``                                        | Public destructor                                                                                |
| ``getLocalEngine()``                 | ``static const std::shared_ptr<Engine>``        | Return a reference to the singleton [Engine][EngDes]                                                |
| ``getLocalObjects()``                | ``std::map<uint32_t, std::shared_ptr<Object>>`` | Return a map containing ``std::shared_ptr``'s to all [Objects][ObjDes] being managed by this [Engine][EngDes] |
| ``getLocalObject(uint32_t)``         | ``std::shared_ptr<Object>``                     | Return a reference to [Object][ObjDes] based on its Id                                              |
| ``createElement<T>()``               | ``std::shared_ptr<T>``                          | Creates a new instance of a template class T deriving from [Circuit Element][EleDes]                |

##### Global Methods

| Name                                 | Return Type                           | Description                                                                                                                                                                         |
|--------------------------------------|---------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| ``createElement<T>()``   | ``std::shared_ptr<T>`` | Global method that access the [Engine][EngDes] singleton's ``createElement<T>()`` method. This global method intended use is to simplify the access to the [Engine][EngDes] singleton instance  |

#### Examples

##### Creating [Circuit Element][EleDes] Instances

```cpp
#include <PamolaEngine.h>

int main()
{
  // Creating resistors (deriving from Circuit Element)
  std::shared_ptr<Resistor> R1 = createElement<Resistor>();   // Copy initialization   
  std::shared_ptr<Resistor> R2(createElement<Resistor>());    // Direct initialization
  auto R3 = createElement<Resistor>();                        // Prefered initialization method
  
  // Creating a capacitor (also deriving from Circuit Element)
  auto C = createElement<Capacitor>():
}
```
