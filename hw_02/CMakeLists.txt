cmake_minimum_required(VERSION 3.5)

set(projectName toutf8)
project(${projectName} VERSION 0.1.0
    DESCRIPTION "Converter from code-paged text to utf-8"
    LANGUAGES C)


add_executable(${projectName} main.c)
target_compile_options(${projectName} PRIVATE -Wall -Wextra -Wpedantic -std=gnu17)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

