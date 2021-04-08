cmake_minimum_required(VERSION 3.17)
project(lol_fala)

set(CMAKE_CXX_STANDARD 14)

add_executable(lol_fala
        main.cpp)


set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

target_link_libraries(lol_fala ${SDL2_LIBRARY})