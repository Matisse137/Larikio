cmake_minimum_required(VERSION 3.20)
project(${PROJECT_NAME} LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Inclure les headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Tous les .cpp de src
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
