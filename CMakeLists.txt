cmake_minimum_required(VERSION 3.17)
project(lol_fala)

set(CMAKE_CXX_STANDARD 14)

add_executable(lol_fala
        main.cpp)


set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

target_link_libraries(lol_fala ${SDL2_LIBRARY})



set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive  -Wl,--no-whole-archive")