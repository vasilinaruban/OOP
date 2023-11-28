cmake_minimum_required(VERSION 3.25.2)
project(Tests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Tests ConstructorTest.cpp GetterTest.cpp LinearizeTest.cpp EquityTest.cpp RotateTest.cpp ChangeTest.cpp)

target_link_libraries(Tests CircularBuffer_Lib)

target_link_libraries(Tests gtest gtest_main)