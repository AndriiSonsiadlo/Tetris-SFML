set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/const")

add_executable(Tetris main.cpp
        TileManager.cpp
        include/TileManager.h
        const/TileConstants.h)
target_link_libraries(Tetris
        PRIVATE
        SFML::Audio
        SFML::Graphics
)
target_include_directories(Tetris PRIVATE ${HEADERS_DIR})

add_dependencies(Tetris copy_assets)
