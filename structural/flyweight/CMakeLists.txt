include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS flyweight)
project(${THIS})

add_executable(flyweight flyweight.cpp)
add_executable(boost_flyweight boost_flyweight.cpp)

target_link_libraries(boost_flyweight pthread)

