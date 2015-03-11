cmake_minimum_required(VERSION 2.8)
project(shaderLoading)

aux_source_directory(. SRC_LIST)

file(GLOB LOAD_SRC "*.hpp" "*.cpp")

add_custom_target(shaderLoading SOURCES ${LOAD_SRC})

# add_executable(${PROJECT_NAME} ${SRC_LIST} ${ALL_SOURCES})
