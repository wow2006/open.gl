set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../Library")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
find_package(SOIL REQUIRED)
include_directories(${SOIL_INCLUDE_DIR})
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})