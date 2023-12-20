cmake_minimum_required(VERSION 3.5)

project(hw_12 LANGUAGES C)

add_executable(hw_12 main.c)

install(TARGETS hw_12
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
