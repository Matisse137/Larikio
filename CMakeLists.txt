cmake_minimum_required(VERSION 3.20)
project(${PROJECT_NAME} Larikio CXX)
set(CMAKE_CXX_STANDARD 17)

# Inclure les headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Tous les .cpp de src
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Larikio ${SOURCES}
        src/main.cpp
        src/launch_manager.cpp
        include/launch_manager.hpp
        include/defines.hpp
        src/exceptions.cpp
        include/exceptions.hpp)
