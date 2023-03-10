cmake_minimum_required(VERSION 3.0)

project(OmegaCore
    VERSION 0.0.1
    DESCRIPTION "Omega Core - Adventure, RPG game"
    LANGUAGES CXX
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(lib)
add_subdirectory(game)
