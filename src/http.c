//
// Created by Andrew Junzki on 3/1/16.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "http.h"
#include "socket.h"

int get_line(int, char*, size_t);
void http_200_ok (int, char*);
void cat (int, char*);

const char* GET = "GET";
const char* POST = "POST";
const size_t URL_MAX_LENGTH = 2084;

const char* base_url = "/Users/andrew";

void
http_handler (int client_sock)
{
    char* buffer;
    char* url = NULL;
    int line_count = 0;
    char* method;
    char full_path[URL_MAX_LENGTH];

    buffer = (char*)malloc(BUFSIZ * sizeof(char));

    // Parse HTTP method
    line_count = get_line(client_sock, buffer, BUFSIZ);
    method = strtok(buffer, " ");
    if (method != NULL)
    {
        url = strtok(NULL, " ");
    }

    sprintf(full_path, "%s%s", base_url, url);
    printf("%s\n", full_path);

    http_200_ok(client_sock, "Content-Type: text/html");
    cat(client_sock, full_path);


    // Parse request body.
    while((line_count > 0) && strcmp("\n", buffer))
    {
        line_count = get_line(client_sock, buffer, BUFSIZ);
    }
}

int
get_line(int sock, char* buffer, size_t size)
{
    char cache = '\0';
    int count = 0;
    ssize_t n_read = 0;

    while ((cache != '\n') && (count < size - 1))
    {
        n_read = recv(sock, &cache, 1, 0);
        if (n_read > 0)
        {
            if (cache == '\r')
            {
                n_read = recv(sock, &cache, 1, MSG_PEEK);
                if ((n_read > 0) && (cache == '\n'))
                    recv(sock, &cache, 1, 0);
                else
                    cache = '\n';
            }
            buffer[count] = cache;
            count += 1;
        }
        else
            cache = '\n';
    }
    buffer[count] = '\0';

    return count;
}

void
http_200_ok (client_sock, content_type)
    int client_sock;
    char* content_type;
{
    char* status = "HTTP/1.1 200 OK\r\n";
    char* content_type_;

    content_type_ = (char*)malloc((sizeof(content_type)+2)*sizeof(char));
    sprintf(content_type_, "%s\r\n", content_type);

    send(client_sock, status, strlen(status)*sizeof(char), 0);
    send(client_sock, content_type_, strlen(content_type_)*sizeof(char), 0);
    send(client_sock, "\r\n", 3, 0);
}

void
cat (int client_sock, char* file_path)
{
    FILE* fp;
    int content_length;
    char* buffer;
    int send_length;

    send_length = 0;

    fp = fopen(file_path, "r");
    if (fp == NULL)
    {
        printf("%d", __LINE__);
    }

    fseek(fp, 0, SEEK_END);
    content_length = (int)ftell(fp);
    rewind(fp);

    buffer = (char*)malloc(BUFSIZ*sizeof(char));
    while (send_length < content_length)
    {
        size_t siz;
        if (content_length < BUFSIZ)
            siz = (size_t)content_length;
        else
            siz = (size_t)BUFSIZ;

        fread(buffer, 1, siz, fp);
        send(client_sock, buffer, siz, 0);
        send_length += siz;
        content_length -= ftell(fp);
    }
}