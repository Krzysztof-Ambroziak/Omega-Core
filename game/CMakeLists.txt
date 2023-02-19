find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(OC-game)

set(source "src")
set(main "${source}/main")
set(game "game")
set(res "resources")

qt5_add_resources(RESOURCES
    ${main}/${res}/tiles.qrc
    ${main}/${res}/maps.qrc
)

target_sources(OC-game
    PRIVATE ${main}/${game}/OmegaCore.cpp
    PRIVATE ${RESOURCES}
)

target_link_libraries(OC-game
    PRIVATE Qt5::Widgets
    PRIVATE Loader
)