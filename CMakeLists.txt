// CMake configuration for the Drinking Philosophers project

cmake_minimum_required(VERSION 3.10)

project(
    DrinkingPhilosophers
    VERSION 0.1
    DESCRIPTION "A C++ implementation of the Drinking Philosophers problem"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)
    