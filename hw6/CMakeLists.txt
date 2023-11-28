cmake_minimum_required(VERSION 3.25)
project(hw5)

set(CMAKE_CXX_STANDARD 17)

add_executable(hw5 main.cpp SmsNotifier.cpp EmailNotifier.h EmailNotifier.cpp INotifier.h SmsNotifier.h)
