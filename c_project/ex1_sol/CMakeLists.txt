cmake_minimum_required(VERSION 3.19)
project(QueenGambit_Spring21 C)

set(CMAKE_C_STANDARD 99)

# Set variables holding flags for gcc
# Set the flags for gcc (can also be done using target_compile_options and a couple of other ways)
set(MTM_FLAGS_DEBUG "-std=c99 --pedantic-errors -Wall -Werror")
set(MTM_FLAGS_RELEASE "${MTM_FLAGS_DEBUG} -DNDBUG")
set(CMAKE_C_FLAGS ${MTM_FLAGS_DEBUG})


# Tell CMake to build an executable named mtm_tot, specifying the comprising file(s)
add_executable(QueenGambit_Spring21 mtm_map/map.c chessSystem.c
        data_types/game.c data_types/player.c data_types/tournament.c
        data_types/chessTournament.c tests/chessSystemTestsExample.c)