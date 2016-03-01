//
//  main.c
//  GatlingHttp
//
//  Created by Andrew Junzki on 3/1/16.
//  Copyright © 2016 Spinel Studio. All rights reserved.
//

#include <stdio.h>
#include "socket.h"
#include "http.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    int server_sock = init_server(9001);
    handle(server_sock, http_handler);
    return 0;
}
