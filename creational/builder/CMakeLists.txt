include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS builder)
project(${THIS})

add_executable(naive_builder naive_builder.cpp)
add_executable(builder builder.cpp)
add_executable(fluent_builder fluent_builder.cpp)
add_executable(groovy_style groovy_style.cpp)
add_executable(facets facets/facets.cpp facets/person.cpp facets/person_builder.cpp facets/person.hpp facets/person_work_builder.hpp facets/person_work_builder.hpp)

