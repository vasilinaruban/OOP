cmake_minimum_required(VERSION 3.25.2)
project(Task_4)

set(CMAKE_CXX_STANDARD 17)

add_executable(Task_4 main.cpp
        SoundProcessor.cpp
        SoundProcessor.h
        WavFile.cpp
        WavFile.h
        Config.cpp
        Config.h
        Link.cpp
        Link.h)
