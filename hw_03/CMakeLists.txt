cmake_minimum_required(VERSION 3.5)

project(hw_03 LANGUAGES C)

add_executable(hw_03 main.c)

install(TARGETS hw_03
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
