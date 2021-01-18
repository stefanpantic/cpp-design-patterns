include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS state)
project(${THIS})

add_executable(state state.cpp)
add_executable(boost_msm boost_msm.cpp)

