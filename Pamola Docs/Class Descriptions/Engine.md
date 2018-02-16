
[Eng]: ../../PamolaProject/PamolaProject/PamolaEngine.h
[Obj]: ../../PamolaProject/PamolaProject/PamolaObject.h
[Cir]: ../../PamolaProject/PamolaProject/Circuit.h   
[Ter]: ../../PamolaProject/PamolaProject/CircuitTerminal.h
[TerCpp]: ../../PamolaProject/PamolaProject/CircuitTerminal.cpp
[Nod]: ../../PamolaProject/PamolaProject/CircuitNode.h
[Ele]: ../../PamolaProject/PamolaProject/CircuitElement.h

# [Pamola](../README.md)
- ## [Class Descriptions](README.md)

  - ### [Pamola::Engine][Eng]

#### Responsabilities

The Pamola [Engine][Eng] class responsibilities are:
- Creating/maintaining all classes deriving from Pamola [Object][Obj] class;
- Supplying access to all classes deriving from [Object][Obj] class;
- Handling all includes into ``<PamolaEngine.h>`` header.

#### Object Creation

Once the program is loaded, a ``static`` [Engine][Eng]  instance is created. This is made in order to allow the user better freedom in creating their own Pamola [Circuit Element][Ele] instances. For the time being, this will be the [Engine][Eng] default behaviour, and thus its constructor is kept ``protected``. Further improvements will focus on removing all static allocation and allowing multiple [Engine][Eng] instances.

#### Memory Handling

All memory is handled dynamically through ``std::shared_ptr`` and ``std::weak_ptr``, in order to avoid leaks and preserve lifetime safety.

#### Members and Methods

##### Public Methods

| Name                                 | Return Type                                     | Description                                                                                      |
|--------------------------------------|-------------------------------------------------|--------------------------------------------------------------------------------------------------|
| ``~Engine()``                        | ``void``                                        | Public destructor                                                                                |
| ``getLocalEngine()``                 | ``static const std::shared_ptr<Engine>``        | Return a reference to the singleton [Engine][Eng]                                                |
| ``getLocalObjects()``                | ``std::map<uint32_t, std::shared_ptr<Object>>`` | Return a map containing ``std::shared_ptr``'s to all objects being managed by this [Engine][Eng] |
| ``getLocalObject(uint32_t)``         | ``std::shared_ptr<Object>``                     | Return a reference to [Object][Obj] based on its Id                                              |
| ``createElement<T>()``               | ``std::shared_ptr<T>``                          | Creates a new instance of a template class T deriving from [Circuit Element][Ele]                |

##### Global Methods

| Name                                 | Return Type                           | Description                                                                                                                                                                         |
|--------------------------------------|---------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| ``createElement<T>()`` | ``std::shared_ptr<T>`` | Global method that access the [Engine][Eng] singleton's ``createElement<T>()`` method. This global method intended use is to simplify the access to the [Engine][Eng] singleton instance.  |
