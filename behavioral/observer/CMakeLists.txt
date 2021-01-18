include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS observer)
project(${THIS})

add_executable(observer observer.cpp)
add_executable(boost_signals2 boost_signals2.cpp)

