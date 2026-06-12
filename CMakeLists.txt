# CMakeLists.txt - Build configuration for the Drinking Philosophers project

cmake_minimum_required(VERSION 3.10)

project(
    DrinkingPhilosophers
    VERSION 0.1
    DESCRIPTION "A C++ implementation of the Drinking Philosophers problem"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    drinking-philosophers-cpp

    src/main.cpp
    src/graphs/graph.cpp
    src/resources/bottle.cpp
    src/resources/bottle_manager.cpp
    src/philosophers/philosopher.cpp
    src/strategies/ordered_strategy.cpp
    src/strategies/waiter_strategy.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(
    drinking-philosophers-cpp
    PRIVATE
    Threads::Threads
)

target_include_directories(
    drinking-philosophers-cpp
    PRIVATE
    src
)

# Copy test data files to the output directory so the executable can find them
configure_file(
    src/cases/case1.txt
    src/cases/case2.txt
    src/cases/case3.txt
    ${CMAKE_CURRENT_BINARY_DIR}
    COPYONLY
)
