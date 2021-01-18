include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS chain_of_responsibility)
project(${THIS})

add_executable(cor_pointer cor_pointer.cpp)
add_executable(cor_broker cor_broker.cpp)

