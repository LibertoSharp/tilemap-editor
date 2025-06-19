cmake_minimum_required(VERSION 3.30)
project(makean_rpg)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(makean_rpg src/main.cpp)
target_link_libraries(makean_rpg PRIVATE SFML::Graphics)
