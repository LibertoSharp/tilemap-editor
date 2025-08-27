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

# --- GoogleTest ---
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

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
        src/GUI/MainGUI.cpp
        src/GUI/Button.cpp
        include/GUI/Button.h
        include/GUI/AnchorsType.h
        include/Common.h
        src/GUI/Dropdown.cpp
        include/GUI/Dropdown.h
        src/GUI/TextElement.cpp
        include/GUI/TextElement.h
        src/GUI/Tilegrid.cpp
        include/GUI/Tilegrid.h
        include/managers/ShaderManager.h
        src/GUI/TextInput.cpp
        include/GUI/TextInput.h
        include/graphics/BackgroundGrid.h
        src/graphics/BackgroundGrid.cpp
        include/engine/DialogExplorer.h
        src/engine/DialogExplorer.cpp
)
target_link_libraries(makean_rpg PRIVATE SFML::Graphics)
target_link_options(makean_rpg PRIVATE "-mwindows")
target_include_directories(makean_rpg PRIVATE ${PROJECT_SOURCE_DIR}/include)

enable_testing()

add_executable(
    test_GuiElement
    test/test_GuiElement.cpp
    include/GUI/GuiElement.h
    src/GUI/GuiElement.cpp
    src/GUI/GuiLayer.cpp
    src/GUI/Tilegrid.cpp
    src/managers/TextureManager.cpp
    src/GUI/Button.cpp
)
target_link_libraries(test_GuiElement PRIVATE gtest_main sfml-graphics sfml-window sfml-system)
target_include_directories(test_GuiElement PRIVATE ${PROJECT_SOURCE_DIR}/include)

include(GoogleTest)
add_test(NAME GuiElementTest COMMAND test_GuiElement)
