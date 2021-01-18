include("${CMAKE_CURRENT_LIST_DIR}/../CMakeConfig.cmake")

set(THIS behavioral)
project(${THIS})

add_subdirectory(chain_of_responsibility)
add_subdirectory(command)
add_subdirectory(interpreter)
add_subdirectory(iterator)
add_subdirectory(mediator)
add_subdirectory(memento)
add_subdirectory(observer)
add_subdirectory(state)
add_subdirectory(strategy)
add_subdirectory(template_method)
add_subdirectory(visitor)

