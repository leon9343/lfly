cmake_minimum_required(VERSION 3.28)
project(lfly VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})


include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRCS src/*.cpp)

add_executable(lfly ${SRCS})
target_link_libraries(lfly PRIVATE ${OpenGL_LIBRARIES})
target_link_libraries(lfly PRIVATE ${SDL2_LIBRARIES})
