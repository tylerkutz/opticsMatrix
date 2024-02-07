# CMakeLists for opticsMatrix
project(opticsMatrix)

message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

# Set up
cmake_minimum_required (VERSION 3.1.1)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

find_package(ROOT REQUIRED)
find_package(ROOT REQUIRED COMPONENTS Core RIO Tree)

set(CMAKE_CXX_FLAGS "-std=c++17")

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cc)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.hh)

set(INCLUDES ${ROOT_INCLUDE_DIR})

include_directories(${INCLUDES} ${CMAKE_SOURCE_DIR}/include)

add_executable(opticsMatrix ${CMAKE_SOURCE_DIR}/opticsMatrix.cc ${SOURCE_FILES} ${HEADER_FILES} ${INCLUDES})
target_link_libraries(opticsMatrix ${ROOT_LIBRARIES})
