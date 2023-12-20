set(This test_sflog)
add_executable(${This} main.c)
target_link_libraries(${This} PRIVATE sflog pthread)
