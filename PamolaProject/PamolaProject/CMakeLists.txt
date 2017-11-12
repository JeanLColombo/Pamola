
add_definitions(-std=c++0x)

add_library(pamola STATIC
	CircuitElement.cpp
	CircuitNode.cpp
	CircuitTerminal.cpp
	PamolaObject.cpp
)

