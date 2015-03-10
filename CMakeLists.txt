cmake_minimum_required(VERSION 2.8)
project(OpenGL_on_SDL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${${PROJECT_NAME}_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lmingw32 -lsdl2main -lglew32")

#find_package(SDL2 REQUIRED)
#include_directories($(SDL2_INCLUDE_DIR))

#find_package(GLEW REQUIRED)
#include_directories($(GLEW_INCLUDE_DIR))

#find_package(OPENGL REQUIRED)
#include_directories($(OPENGL_INCLUDE_DIR))

aux_source_directory(. SRC_LIST)
