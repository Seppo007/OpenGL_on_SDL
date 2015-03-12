cmake_minimum_required(VERSION 2.8)
project(texturing)

aux_source_directory(. SRC_LIST)

file(GLOB ALL_SOURCES "*.hpp" "*.cpp" "*.vert" "*.frag" "*.bmp")

add_executable(${PROJECT_NAME} ${SRC_LIST} ${ALL_SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
