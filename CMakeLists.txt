cmake_minimum_required(VERSION 3.20)
project(Larikio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Dossiers ===
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external/imgui
        ${CMAKE_SOURCE_DIR}/external/imgui/backends
        ${CMAKE_SOURCE_DIR}/external/glfw/include
)

# === Sources ===
file(GLOB_RECURSE SOURCES "src/*.cpp")

set(IMGUI_SRC
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_demo.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
        src/gui.cpp
        include/gui.hpp
)

# === GLFW ===
add_subdirectory(external/glfw)

# === Exécutable principal ===
add_executable(Larikio
        ${SOURCES}
        ${IMGUI_SRC}
)

# === Liens ===
if (WIN32)
    target_link_libraries(Larikio PRIVATE glfw opengl32)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    target_link_libraries(Larikio PRIVATE glfw ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
else() # Linux
    target_link_libraries(Larikio PRIVATE glfw ${GLFW_LIBRARIES} dl pthread GL)
endif()

# === Options ===
set_target_properties(Larikio PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
