include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS iterator)
project(${THIS})

add_executable(std_iterator std_iterator.cpp)
add_executable(iterator iterator.cpp)
add_executable(boost_iterator boost_iterator_facade.cpp)

