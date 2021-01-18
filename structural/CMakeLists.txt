include("${CMAKE_CURRENT_LIST_DIR}/../CMakeConfig.cmake")

set(THIS structural)
project(${THIS})

add_subdirectory(adapter)
add_subdirectory(bridge)
add_subdirectory(composite)
add_subdirectory(decorator)
add_subdirectory(facade)
add_subdirectory(flyweight)
add_subdirectory(nullobject)
add_subdirectory(proxy)

