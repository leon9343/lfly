cmake_minimum_required(VERSION 3.28)
project(lfly VERSION 1.0 LANGUAGES C CXX)


# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/src)

# GLAD
add_library(glad STATIC src/External/src/glad.c)
target_include_directories(glad PUBLIC src/External/include)

file(GLOB_RECURSE SRCS src/*.cpp)
add_executable(lfly ${SRCS})

target_link_libraries(lfly PRIVATE
  glad
  ${OpenGL_LIBRARIES}
  ${SDL2_LIBRARIES}
  ${CMAKE_DL_LIBS}
)

