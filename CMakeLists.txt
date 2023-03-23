cmake_minimum_required(VERSION 3.24)
project(cpp-tutorial)

set(CMAKE_CXX_STANDARD 17)

###### hello-world.cpp #####
set(_SRC ${CMAKE_CURRENT_SOURCE_DIR}/hello-world.cpp)

###### hello-world-ii #####
set(_OLD_OUTPUT ${_SRC})
set(_OUTPUT ${_SRC}.ii)
add_custom_command(
  OUTPUT ${_OUTPUT}
  DEPENDS ${_OLD_OUTPUT}
  COMMAND ${CMAKE_CXX_COMPILER} -E ${_OLD_OUTPUT} -o ${_OUTPUT}
)
add_custom_target(hello-world-ii DEPENDS ${_OUTPUT})

###### hello-world-s #####
set(_OLD_OUTPUT ${_OUTPUT})
set(_OUTPUT ${_SRC}.s)
add_custom_command(
  OUTPUT ${_OUTPUT}
  DEPENDS ${_OLD_OUTPUT}
  COMMAND ${CMAKE_CXX_COMPILER} -S ${_OLD_OUTPUT} -o ${_OUTPUT}
)
add_custom_target(hello-world-s DEPENDS ${_OUTPUT})

###### hello-world-o #####
set(_OLD_OUTPUT ${_OUTPUT})
set(_OUTPUT ${_SRC}.o)
add_custom_command(
  OUTPUT ${_OUTPUT}
  DEPENDS ${_OLD_OUTPUT}
  COMMAND ${CMAKE_CXX_COMPILER} -c ${_OLD_OUTPUT} -o ${_OUTPUT}
)
add_custom_target(hello-world-o DEPENDS ${_OUTPUT})

###### hello-world #####
set(_OLD_OUTPUT ${_OUTPUT})
set(_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/hello-world)
add_custom_command(
  OUTPUT ${_OUTPUT}
  DEPENDS ${_OLD_OUTPUT}
  COMMAND ${CMAKE_CXX_COMPILER} ${_OLD_OUTPUT} -o ${_OUTPUT}
)
add_custom_target(hello-world DEPENDS ${_OUTPUT} SOURCES ${_SRC})

###### hello-world-src #####
add_executable(hello-world-src ${_SRC})
