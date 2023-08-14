add_executable(zipjpeg main.c)

install(TARGETS zipjpeg
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

