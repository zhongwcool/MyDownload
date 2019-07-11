cmake_minimum_required(VERSION 3.14)
project(MyDownload C)

set(CMAKE_C_STANDARD 99)

#include_directories(include)

#link_directories(lib)

add_executable(jsupdate
        src/main.c
        #src/example/10-at-a-time.c
        src/util/time_util.c
        src/util/time_util.h
        )

target_link_libraries(jsupdate
        #util/download.c
        libcurl.so
        )