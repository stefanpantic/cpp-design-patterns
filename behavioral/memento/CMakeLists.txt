include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS memento)
project(${THIS})

add_executable(memento memento.cpp)
add_executable(undo_redo undo_redo.cpp)

