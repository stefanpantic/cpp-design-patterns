include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS visitor)
project(${THIS})

add_executable(double_dispatch double_dispatch/visitor.cpp double_dispatch/model.hpp double_dispatch/visitor.hpp)
add_executable(multiple_dispatch multiple_dispatch/visitor.cpp)

