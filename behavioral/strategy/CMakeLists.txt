include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS strategy)
project(${THIS})

add_executable(strategy strategy.cpp)
add_executable(policy policy.cpp)

