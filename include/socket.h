#ifndef GHD_SOCKET_H_
#define GHD_SOCKET_H_

int  init_server(unsigned short);
void handle(int, void (*)(int));

#endif /* GHD_SOCKET_H_ */
