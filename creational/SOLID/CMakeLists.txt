include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS SOLID)
project(${THIS})

add_executable(SRP SRP.cpp)
add_executable(OCP OCP.cpp)
add_executable(LSP LSP.cpp)
add_executable(ISP ISP.cpp)
add_executable(DIP DIP.cpp di.hpp)

