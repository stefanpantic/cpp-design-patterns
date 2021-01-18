include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS factory)
project(${THIS})

add_executable(factory factory.cpp)
add_executable(factory_method factory_method.cpp)
add_executable(inner_factory inner_factory.cpp)
add_executable(abstract_factory abstract_factory/abstract_factory.cpp abstract_factory/abstract_hot_drink_factory.hpp abstract_factory/coffee_factory.hpp abstract_factory/drink_factory.hpp abstract_factory/hot_drink.hpp abstract_factory/tea_factory.hpp)

