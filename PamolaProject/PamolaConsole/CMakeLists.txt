
add_definitions(-std=c++0x)

include_directories(${CMAKE_SOURCE_DIR}/PamolaProject)
include_directories(${CMAKE_BINARY_DIR}/PamolaProject)

add_executable(program Learning.cpp  PamolaConsole.cpp)

target_link_libraries(program pamola)

