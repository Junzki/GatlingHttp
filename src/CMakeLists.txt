cmake_minimum_required(VERSION 3.8)


set(SOURCE_FILES
    http.h http.c
    socket.c
    main.c)

add_executable(gating-httpd ${SOURCE_FILES})
