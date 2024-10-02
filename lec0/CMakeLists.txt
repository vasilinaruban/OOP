cmake_minimum_required(VERSION 3.25)
project(bebra)

set(CMAKE_CXX_STANDARD 20)

add_executable(bebra main.cpp Rational.h Rational.cpp)
