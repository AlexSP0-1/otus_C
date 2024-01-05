cmake_minimum_required(VERSION 3.5)

project(hw_14 LANGUAGES C)

add_executable(hw_14 main.c)

install(TARGETS hw_14
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
