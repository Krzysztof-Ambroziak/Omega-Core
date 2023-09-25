find_package(Qt5 COMPONENTS Gui REQUIRED)

cmake_minimum_required(VERSION 3.11)

project(OmegaCore_Library
    VERSION 1.0.0
    DESCRIPTION "Maps and tiles loader library"
)

add_library(Loader SHARED)

target_compile_features(Loader
    PRIVATE cxx_std_17
)

target_sources(Loader
    PRIVATE "loader/src/loader/Definitions.hpp"
    PRIVATE "loader/src/loader/Loader.cpp"
    PRIVATE "loader/src/loader/Map.cpp"
    PRIVATE "loader/src/loader/MapLoader.hpp"
    PRIVATE "loader/src/loader/MapLoader.cpp"
    PRIVATE "loader/src/loader/Sprite.cpp"
    PRIVATE "loader/src/loader/SpriteLoader.hpp"
    PRIVATE "loader/src/loader/SpriteLoader.cpp"
    PRIVATE "loader/src/loader/SpriteSheet.cpp"
    PRIVATE "loader/src/loader/TileLoader.hpp"
    PRIVATE "loader/src/loader/TileLoader.cpp"
    PRIVATE "loader/src/loader/utilities/api/ITileCutter.hpp"
    PRIVATE "loader/src/loader/utilities/IsometricTileCutter.hpp"
    PRIVATE "loader/src/loader/utilities/IsometricTileCutter.cpp"
    PRIVATE "loader/src/loader/utilities/NullTileCutter.hpp"
    PRIVATE "loader/src/loader/utilities/PrivateHelpers.hpp"
    PRIVATE "loader/src/loader/utilities/SquaredTileCutter.hpp"
    PRIVATE "loader/src/loader/utilities/SquaredTileCutter.cpp"
    PRIVATE "loader/src/loader/utilities/TileCutterAdapter.hpp"
    PRIVATE "loader/src/loader/utilities/TileCutterAdapter.cpp"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/loader/include/Commons.hpp"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/loader/include/loader/Map.hpp"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/loader/include/loader/Sprite.hpp"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/loader/include/loader/SpriteSheet.hpp"
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/loader/include/loader/Loader.hpp"
)

target_include_directories(Loader
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/loader/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/loader/src
)

target_link_libraries(Loader
    PRIVATE Qt5::Gui
)

####################################
add_library(Observer INTERFACE)

target_sources(Observer
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/dp/include/Observable.hpp"
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/dp/include/Observer.hpp"
)

target_include_directories(Observer
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/dp/include
)
