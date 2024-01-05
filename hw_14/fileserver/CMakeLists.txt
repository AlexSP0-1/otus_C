cmake_minimum_required(VERSION 3.5)

set(This fileserver)
add_executable(${This}
  main.c
  connection.c
  sock_helpers.c
  signal_helpers.c
  buffer.c
)
target_include_directories(${This} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sflog)
target_link_libraries(${This} sflog)
