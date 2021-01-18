include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS adapter)
project(${THIS})

add_executable(std_stack std_stack.cpp)
add_executable(adapter adapter.cpp)
add_executable(geometry geometry/draw.cpp geometry/geometry.hpp)

