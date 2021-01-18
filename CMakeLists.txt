cmake_minimum_required(VERSION 3.16)

set(THIS cpp-design-patterns)
project(${THIS})

include("${CMAKE_CURRENT_LIST_DIR}/CMakeConfig.cmake")

add_subdirectory(creational)
add_subdirectory(structural)
add_subdirectory(behavioral)

