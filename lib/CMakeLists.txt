find_package(Qt5 COMPONENTS Gui REQUIRED)

cmake_minimum_required(VERSION 3.11)
project(Loader-Library
    VERSION 1.0.0
    DESCRIPTION "Maps and tiles loader library"
)

add_library(Loader SHARED)

target_sources(Loader
    PRIVATE "loader/src/loader/Definitions.hpp"
    PRIVATE "loader/src/loader/Loader.cpp"
    PRIVATE "loader/src/loader/TileSheet.cpp"
    PRIVATE "loader/src/loader/TileLoader.hpp"
    PRIVATE "loader/src/loader/TileLoader.cpp"
    PRIVATE "loader/src/loader/utilities/api/ITileCutter.hpp"
    PRIVATE "loader/src/loader/utilities/IsometricTileCutter.hpp"
    PRIVATE "loader/src/loader/utilities/IsometricTileCutter.cpp"
    PRIVATE "loader/src/loader/utilities/NullTileCutter.hpp"
    PRIVATE "loader/src/loader/utilities/SquaredTileCutter.hpp"
    PRIVATE "loader/src/loader/utilities/SquaredTileCutter.cpp"
    PRIVATE "loader/src/loader/utilities/TileCutterAdapter.hpp"
    PRIVATE "loader/src/loader/utilities/TileCutterAdapter.cpp"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/loader/include/loader/Commons.hpp"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/loader/include/loader/TileSheet.hpp"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/loader/include/loader/Loader.hpp"
)

target_include_directories(Loader
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/loader/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/loader/src
)      

target_link_libraries(Loader
    PRIVATE Qt5::Gui
)
