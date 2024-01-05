set(This sflog)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(${This} sflog.c)

target_link_libraries(${This} Threads::Threads)
target_include_directories(${This} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
