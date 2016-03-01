//
//  socket.c
//  GatlingHttp
//
//  Created by 孟凡钧 on 3/1/16.
//  Copyright © 2016 Spinel Studio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "socket.h"

void die(const char*);

void
die(const char* error_msg)
{
    perror(error_msg);
    exit(EXIT_FAILURE);
}

int
init_server (unsigned short bind_port)
{
    int httpd;
    struct sockaddr_in name;
    
    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
    {
        die("Cannot setup socket");
    }
    
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(bind_port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(httpd, (struct sockaddr*)&name, sizeof(name)) < 0)
    {
        die("Bind error");
    }
    
    if (listen(httpd, 5) < 0)
    {
        die("Cannot start listening");
    }
    
    return httpd;
}



void
handle (int server_sock, void (*handler)(int)) {
    int client_sock;
    struct sockaddr_in client_name;
    unsigned int client_len;


    client_len = sizeof(client_name);

    client_sock = accept(server_sock, (struct sockaddr *) &client_name, &client_len);
    if (client_sock == -1) {
        die("Cannot start client");
    }

    handler(client_sock);

    close(client_sock);
}



