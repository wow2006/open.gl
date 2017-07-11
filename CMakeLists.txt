cmake_minimum_required(VERSION 3.1)
project("open.gl")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

find_package(OpenGL REQUIRED)
find_package(GLFW3  REQUIRED)
find_package(GLEW   REQUIRED)
find_package(SOIL   REQUIRED)
find_package(GLM    REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_definitions("-std=c++14")

add_subdirectory("1- Context Creation")
add_subdirectory("2- Drawing polygons")
add_subdirectory("3- Textures")
add_subdirectory("4- Transformations")
add_subdirectory("5- Depth and stencils")
add_subdirectory("6- Frame buffers")
add_subdirectory("7- Geometry shaders")
add_subdirectory("8- Transform Feedback")
