include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS decorator)
project(${THIS})

add_executable(functional_decorator functional_decorator.cpp)
add_executable(wrapping_decorator wrapping_decorator.cpp)
add_executable(mixin_inheritance mixin_inheritance.cpp)

