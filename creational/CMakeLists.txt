include("${CMAKE_CURRENT_LIST_DIR}/../CMakeConfig.cmake")

set(THIS creational)
project(${THIS})

add_subdirectory(SOLID)
add_subdirectory(builder)
add_subdirectory(factory)
add_subdirectory(monads)
add_subdirectory(prototype)
add_subdirectory(singleton)

