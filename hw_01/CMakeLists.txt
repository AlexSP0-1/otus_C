add_executable(zipjpeg main.c)

target_compile_options(zipjpeg PRIVATE -Wall -Wextra -Wpedantic -std=gnu17)

if(UNIX)
    enable_testing()
    add_test(NAME zipjpeg_test COMMAND sh -c "${CMAKE_BINARY_DIR}/hw_01/zipjpeg ${CMAKE_SOURCE_DIR}/testfiles/zipjpeg.jpg | wc -l")
    set_tests_properties(zipjpeg_test PROPERTIES PASS_REGULAR_EXPRESSION "185")

    add_test(NAME jpeg_test COMMAND sh -c "${CMAKE_BINARY_DIR}/hw_01/zipjpeg ${CMAKE_SOURCE_DIR}/testfiles/non-zipjpeg.jpg")
    set_tests_properties(jpeg_test PROPERTIES PASS_REGULAR_EXPRESSION "is a Jpeg")

    add_test(NAME empty_file_test COMMAND sh -c "${CMAKE_BINARY_DIR}/hw_01/zipjpeg  ${CMAKE_SOURCE_DIR}/testfiles/empty")
    set_tests_properties(empty_file_test PROPERTIES PASS_REGULAR_EXPRESSION "is not a Jpeg or ZipJpeg")

    add_test(NAME text_file_test COMMAND sh -c "${CMAKE_BINARY_DIR}/hw_01/zipjpeg  ${CMAKE_SOURCE_DIR}/testfiles/text")
    set_tests_properties(text_file_test PROPERTIES PASS_REGULAR_EXPRESSION "is not a Jpeg or ZipJpeg")

    add_test(NAME nonexist_file_test COMMAND sh -c "${CMAKE_BINARY_DIR}/hw_01/zipjpeg  file_not_exist")
    set_tests_properties(nonexist_file_test PROPERTIES WILL_FAIL true)

endif()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

install(TARGETS zipjpeg
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

