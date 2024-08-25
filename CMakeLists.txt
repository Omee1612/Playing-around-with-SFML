cmake_minimum_required(VERSION 3.27)
project(game)
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)
set(CMAKE_CXX_STANDARD 23)
# Link SFML libraries
add_executable(game main.cpp
        game.h
        game.cpp)
target_link_libraries(game sfml-graphics )
