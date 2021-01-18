include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS bridge)
project(${THIS})

add_executable(shape_sizing shape_sizing.cpp)
add_executable(pimpl pimpl/pimpl.cpp pimpl/person.cpp pimpl/person.hpp)

