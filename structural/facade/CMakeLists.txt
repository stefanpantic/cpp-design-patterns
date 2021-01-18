include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS facade)
project(${THIS})

add_executable(facade facade.cpp buffer.hpp console.hpp viewport.hpp window.hpp)

