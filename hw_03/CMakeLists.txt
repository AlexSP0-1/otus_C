cmake_minimum_required(VERSION 3.5)

project("hw_03"
    VERSION 0.0.1
    DESCRIPTION "homework for out c developer course"
    LANGUAGES C)

add_subdirectory(maplib)
add_subdirectory(wordcount)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
