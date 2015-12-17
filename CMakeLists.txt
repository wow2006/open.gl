cmake_minimum_required(VERSION 2.8)
project("open.gl")

include ("${CMAKE_CURRENT_LIST_DIR}/cmake/include_libraries.cmake")
include ("${CMAKE_CURRENT_LIST_DIR}/cmake/Utility.cmake")

add_subdirectory("1- Context Creation")
add_subdirectory("2- Drawing polygons")
add_subdirectory("3- Textures")
add_subdirectory("4- Transformations")
add_subdirectory("5- Depth and stencils")
add_subdirectory("6- Frame buffers")
add_subdirectory("7- Geometry shaders")
add_subdirectory("8- Transform Feedback")
