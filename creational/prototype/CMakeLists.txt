include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS prototype)
project(${THIS})

add_executable(prototype prototype.cpp)
add_executable(prototype_factory prototype_factory.cpp)
add_executable(serialization serialization.cpp)

target_link_libraries(serialization boost_serialization)

