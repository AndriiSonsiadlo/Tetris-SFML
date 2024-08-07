set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/const")

add_executable(Tetris
        main.cpp
        const/TileConstants.h
        const/TetrominoConstants.h
        include/TileManager.h
        TileManager.cpp
        include/TetrominoManager.h
        TetrominoManager.cpp
)
target_link_libraries(Tetris
        PRIVATE
        SFML::Audio
        SFML::Graphics
)
target_include_directories(Tetris PRIVATE ${HEADERS_DIR})

add_dependencies(Tetris copy_assets)
