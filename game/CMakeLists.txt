find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(OC-game)

set(source "src")
set(main "${source}/main")
set(game "game")

target_sources(OC-game
    PRIVATE ${main}/${game}/OmegaCore.cpp
)

target_link_libraries(OC-game
    PRIVATE Qt5::Widgets
)
