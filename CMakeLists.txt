cmake_minimum_required(VERSION 4.0)

project(Tetris)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Tetris src/main.cpp)
target_link_libraries(Tetris
    PRIVATE
        SFML::Audio
        SFML::Graphics
)
