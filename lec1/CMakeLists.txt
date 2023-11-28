cmake_minimum_required(VERSION 3.25.2)
project(lec1)

set(CMAKE_CXX_STANDARD 20)

include_directories(./)

add_library(CircularBuffer_Lib SHARED CircularBuffer.h)

set_target_properties(CircularBuffer_Lib PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(test)

add_executable(CircularBuffer main.cpp test/ConstructorTest.cpp test/ConstructorTest.cpp test/ConstructorTest.cpp)

target_link_libraries(CircularBuffer PRIVATE CircularBuffer_Lib)