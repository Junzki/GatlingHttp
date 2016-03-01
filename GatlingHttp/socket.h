//
//  socket.h
//  GatlingHttp
//
//  Created by 孟凡钧 on 3/1/16.
//  Copyright © 2016 Andrew Junzki. All rights reserved.
//

#ifndef socket_h
#define socket_h

#define BUF_SIZ 512

int init_server(unsigned short);
void handle(int, void (*)(int));

#endif /* socket_h */
