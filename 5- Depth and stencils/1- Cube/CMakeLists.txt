project(Cube)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW3_INCLUDE_PATH} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${SOIL_INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARIES} ${GLFW3_LIBRARY} ${SOIL_LIBRARY})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/media/*.png" ${CMAKE_BINARY_DIR}/bin/)
