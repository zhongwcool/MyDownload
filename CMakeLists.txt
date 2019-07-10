cmake_minimum_required(VERSION 3.14)
project(MyDownload C)

set(CMAKE_C_STANDARD 99)

#include_directories(include)

#link_directories(lib)

add_executable(MyDownload
        src/main.c
        #src/example/10-at-a-time.c
        )

target_link_libraries(MyDownload
        #util/download.c
        libcurl.so
        )