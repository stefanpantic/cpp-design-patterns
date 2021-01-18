include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS iterpreter)
project(${THIS})

add_executable(interpreter interpreter.cpp)

