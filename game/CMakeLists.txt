find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(OC-game)

set(source "src")
set(main "${source}/main")
set(engine "engine")
set(game "game")
set(gui "gui")
set(models "models")
set(renderers "renderers")
set(services "services")
set(interface "api")
set(res "resources")

qt5_add_resources(RESOURCES
    ${main}/${res}/tiles.qrc
    ${main}/${res}/sprites.qrc
    ${main}/${res}/maps.qrc
)

target_sources(OC-game
    PRIVATE ${main}/OCGlobal.hpp
    PRIVATE ${main}/${game}/OmegaCore.cpp
    PRIVATE ${main}/${engine}/Controller.hpp
    PRIVATE ${main}/${engine}/Controller.cpp
    PRIVATE ${main}/${engine}/Timer.hpp
    PRIVATE ${main}/${engine}/Timer.cpp
    PRIVATE ${main}/${gui}/Window.hpp
    PRIVATE ${main}/${gui}/Window.cpp
    PRIVATE ${main}/${models}/AssetsModel.hpp
    PRIVATE ${main}/${models}/AssetsModel.cpp
    PRIVATE ${main}/${models}/MapModel.hpp
    PRIVATE ${main}/${models}/MapModel.cpp
    PRIVATE ${main}/${models}/ScreenModel.hpp
    PRIVATE ${main}/${models}/ScreenModel.cpp
    PRIVATE ${main}/${models}/${interface}/IMapModel.hpp
    PRIVATE ${main}/${models}/${interface}/IScreenModel.hpp
    PRIVATE ${main}/${renderers}/NullRenderer.hpp
    PRIVATE ${main}/${renderers}/TileRenderer.hpp
    PRIVATE ${main}/${renderers}/TileRenderer.cpp
    PRIVATE ${main}/${renderers}/${interface}/IRenderer.hpp
    PRIVATE ${main}/${services}/MapService.hpp
    PRIVATE ${main}/${services}/MapService.cpp
    PRIVATE ${main}/${services}/TileRenderingService.hpp
    PRIVATE ${main}/${services}/TileRenderingService.cpp
    PRIVATE ${RESOURCES}
)

target_link_libraries(OC-game
    PRIVATE Qt5::Widgets
    PRIVATE Loader
)
