include("${CMAKE_CURRENT_LIST_DIR}/../../CMakeConfig.cmake")

set(THIS mediator)
project(${THIS})

add_executable(broker broker.cpp)
add_executable(chat_room chat_room/chat_room.cpp chat_room/mediator.cpp chat_room/person.cpp chat_room/chat_room.hpp chat_room/person.hpp)

