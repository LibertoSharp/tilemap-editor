cmake_minimum_required(VERSION 3.30)
project(makean_rpg)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(makean_rpg src/main.cpp
        src/level/Grid.cpp
        include/level/Grid.h
        src/level/Tile.cpp
        include/level/Tile.h
        src/engine/Application.cpp
        include/engine/Application.h
        src/level/TileInfo.cpp
        include/level/TileInfo.h
        src/managers/TextureManager.cpp
        include/managers/TextureManager.h
        include/managers/AssetLoader.h
        include/engine/Singleton.h
        src/graphics/PixelPerfectRenderTarget.cpp
        include/graphics/PixelPerfectRenderTarget.h
        src/level/Level.cpp
        include/level/Level.h
        src/engine/Editor.cpp
        include/engine/Editor.h
        src/GUI/GuiElement.cpp
        include/GUI/GuiElement.h
        src/GUI/GuiLayer.cpp
        include/GUI/GuiLayer.h
        include/GUI/MainGUI.h
        src/GUI/Button.cpp
        include/GUI/Button.h)
target_link_libraries(makean_rpg PRIVATE SFML::Graphics)
target_include_directories(makean_rpg PRIVATE ${PROJECT_SOURCE_DIR}/include)


