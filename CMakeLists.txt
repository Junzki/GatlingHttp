cmake_minimum_required(VERSION 3.3)
project(GatlingHttp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    GatlingHttp/main.c
    GatlingHttp/socket.c
    GatlingHttp/socket.h GatlingHttp/http.c GatlingHttp/http.c GatlingHttp/http.h)

add_executable(GatlingHttp ${SOURCE_FILES})