cmake_minimum_required(VERSION 3.5)

project("sflog"
    VERSION 0.0.1
    DESCRIPTION "SImple log-to-file logger with backtrace"
    LANGUAGES C
)

add_compile_options(-std=gnu17 -ggdb -Wall -Wpedantic -Werror=implicit-function-declaration)
add_link_options(-rdynamic)

add_subdirectory(sflog)

add_subdirectory(test)
