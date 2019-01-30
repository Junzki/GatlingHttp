//
// Created by Andrew Junzki on 3/1/16.
//

#ifndef GHD_HTTP_H_
#define GHD_HTTP_H_

void http_handler (int);

typedef enum {
    GET,
    POST,
    PUT,
    DELETE,
    HEAD,
    OPTION
} ghd_http_method;

typedef struct {
    int fd;

    ghd_http_method method;
    char* raw;

    char* path;
    char* query_string;
    char* data;

} ghd_http_request;

#endif /* GHD_HTTP_H_ */
