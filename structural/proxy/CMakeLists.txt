include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS proxy)
project(${THIS})

add_executable(std_smart_pointers std_smart_pointers.cpp)
add_executable(virtual_proxy virtual_proxy.cpp)
add_executable(communication_proxy communication_proxy.cpp)

