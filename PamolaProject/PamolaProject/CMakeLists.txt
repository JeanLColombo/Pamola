
add_definitions(-std=c++0x)

file(DOWNLOAD
	https://raw.githubusercontent.com/mrange/cpplinq/cpplinq-20140323/CppLinq/cpplinq.hpp
	${CMAKE_BINARY_DIR}/PamolaProject/cpplinq.hpp
	SHOW_PROGRESS)
include_directories(${CMAKE_BINARY_DIR}/PamolaProject)

add_library(pamola STATIC
	CircuitElement.cpp
	CircuitNode.cpp
	CircuitTerminal.cpp
	PamolaObject.cpp
)

