include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS command)
project(${THIS})

add_executable(command command.cpp)
add_executable(composite_command composite_command.cpp)

