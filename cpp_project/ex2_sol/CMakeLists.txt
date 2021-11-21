cmake_minimum_required(VERSION 3.19)
project(ex2_mtm)

set(CMAKE_CXX_STANDARD 11)

# Define variables containing compiler flags for gcc
set(MTM_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDEBUG")

# Set the flags for gcc
set(CMAKE_CPP_FLAGS ${MTM_FLAGS_DEBUG})

# Add the names of your source files here
set(CPP_FILES cmake-build-debug---csl3)

add_executable(ex2_mtm partB/Exceptions.cpp partB/Board.h partB/Character.cpp partB/Soldier.cpp partB/Game.cpp
        partB/Auxiliaries.cpp partB/Sniper.cpp partB/Sniper.h partB/Medic.h partB/Medic.cpp partB/gameTest.cpp)
