cmake_minimum_required(VERSION 3.8)


add_library(ghd_http http.c)

set(SOURCE_FILES
    socket.c
    main.c)

add_executable(gating-httpd ${SOURCE_FILES})
target_link_libraries(gatling-httpd ghd_http)
