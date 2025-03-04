cmake_minimum_required(VERSION 3.10)
project(Tetris)

set(SOURCE_FILES
        ../main.cpp
        src/board.cpp
        src/game.cpp
        menu/menu.cpp
        name/name.cpp
)

add_executable(main ${SOURCE_FILES})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(main PRIVATE sfml-graphics sfml-audio)