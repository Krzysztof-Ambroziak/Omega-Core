find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(OC-game)

set(source "src")
set(main "${source}/main")
set(game "game")
set(gui "gui")
set(renderers "renderers")
set(interface "api")
set(res "resources")

qt5_add_resources(RESOURCES
    ${main}/${res}/tiles.qrc
    ${main}/${res}/maps.qrc
)

target_sources(OC-game
    PRIVATE ${main}/OCGlobal.hpp
    PRIVATE ${main}/${game}/OmegaCore.cpp
    PRIVATE ${main}/${gui}/Window.hpp
    PRIVATE ${main}/${gui}/Window.cpp
    PRIVATE ${main}/${renderers}/NullRenderer.hpp
    PRIVATE ${main}/${renderers}/${interface}/IRenderer.hpp
    PRIVATE ${RESOURCES}
)

target_link_libraries(OC-game
    PRIVATE Qt5::Widgets
    PRIVATE Loader
)
