include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS singleton)
project(${THIS})

add_executable(singleton singleton_tests.cpp singleton.hpp)

