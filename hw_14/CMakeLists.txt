cmake_minimum_required(VERSION 3.5)

project("fileserver"
    VERSION 0.0.1
    DESCRIPTION "hw_14 otus-c http fileserver"
    LANGUAGES C)

add_compile_options(-std=gnu17 -Wall -Wextra -Wpedantic -Werror=implicit-function-declaration)
add_link_options(-rdynamic)
add_subdirectory(sflog)
