set(HEADER_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/const")

file(GLOB_RECURSE HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/const/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/const/*.hpp"
)

add_executable(Tetris
        main.cpp
        ${HEADERS}
        TileManager.cpp
        TetrominoManager.cpp
        TetrominoShape.cpp
        GameController.cpp
        GameStats.cpp
        GameUI.cpp
        Game.cpp
        Playfield.cpp
        Tetromino.cpp
        InputHandler.cpp
)
target_link_libraries(Tetris
        PRIVATE
        SFML::Audio
        SFML::Graphics
)
target_include_directories(Tetris PRIVATE ${HEADER_DIRS})

add_dependencies(Tetris copy_assets copy_fonts)
