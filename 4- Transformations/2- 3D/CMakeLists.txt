project(3D)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${SOIL_LIBRARY})
copySample("${CMAKE_SOURCE_DIR}/media/*.png")
