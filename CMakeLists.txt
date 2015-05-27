cmake_minimum_required(VERSION 2.8)
project(OpenGL_on_SDL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${${PROJECT_NAME}_SOURCE_DIR}/cmake/modules/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++1y")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lmingw32 -lsdl2main -lSDL2_Mixer -lglew32")

find_package(SDL2 REQUIRED)
include_directories($(SDL2_INCLUDE_DIR))
find_package(SDL2_MIXER REQUIRED)

find_package(GLEW REQUIRED)
include_directories($(GLEW_INCLUDE_DIR))

find_package(OPENGL REQUIRED)
include_directories($(OPENGL_INCLUDE_DIR))

aux_source_directory(. SRC_LIST)

add_subdirectory(shaderLoading)
add_subdirectory(firstsdlwin)
add_subdirectory(firstSteps)
add_subdirectory(transformations)
add_subdirectory(multipleObjects)
add_subdirectory(coloring)
add_subdirectory(texturing)
add_subdirectory(sdlwinptr)
add_subdirectory(sdlmixer)
