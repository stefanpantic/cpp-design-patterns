include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS composite)
project(${THIS})

add_executable(composite composite.cpp)
add_executable(geometric geometric.cpp)
add_executable(neurons neurons.cpp)

