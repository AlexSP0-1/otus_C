cmake_minimum_required(VERSION 3.5)

set(projectName toutf8)
project(${projectName} VERSION 0.1.0
    DESCRIPTION "Converter from code-paged text to utf-8"
    LANGUAGES C)


add_executable(${projectName} main.c)
target_compile_options(${projectName} PRIVATE -Wall -Wextra -Wpedantic -std=gnu17)

if(UNIX)
    enable_testing()

    set(TestDir ${CMAKE_SOURCE_DIR}/test)

    add_test(NAME cp1251_test COMMAND sh -c
        "${CMAKE_BINARY_DIR}/${projectName} ${TestDir}/cp1251.txt cp1251 out.txt && diff ${TestDir}/utf8.txt out.txt")

    add_test(NAME iso8859_test COMMAND sh -c
        "${CMAKE_BINARY_DIR}/${projectName} ${TestDir}/iso-8859-5.txt iso-8859-5 out.txt && diff ${TestDir}/utf8.txt out.txt")

    add_test(NAME koi8_test COMMAND sh -c
        "${CMAKE_BINARY_DIR}/${projectName} ${TestDir}/koi8.txt koi8-r out.txt && diff ${TestDir}/utf8.txt out.txt")

    add_test(NAME wrong_cp_test COMMAND sh -c
        "${CMAKE_BINARY_DIR}/${projectName} ${TestDir}/koi8.txt cp1251 out.txt && diff ${TestDir}/utf8.txt out.txt")
    set_tests_properties(wrong_cp_test PROPERTIES WILL_FAIL true)

endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

