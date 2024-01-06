cmake_minimum_required(VERSION 3.5)

project(hw_16 LANGUAGES C)

add_executable(hw_16 main.c)

install(TARGETS hw_16
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
