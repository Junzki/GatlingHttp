#include <strings.h>
#include <arpa/inet.h>
#include <poll.h>
#include "asset.h"
#include "socket.h"


int  init_client(int, struct pollfd*);
void cast_ipaddress(char**, struct sockaddr_in);
void close_conn(struct pollfd*);


int
init_server (unsigned short bind_port)
{
    int    serverfd;
    struct sockaddr_in name;
    
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == serverfd)
        DIE("Cannot setup socket.")
    
    bzero(&name, sizeof(struct sockaddr_in));
    name.sin_family      = AF_INET;
    name.sin_port        = htons(bind_port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (0 > bind(serverfd, (struct sockaddr*)&name, sizeof(name)))
        DIE("Bind error.");
    
    if (0 > listen(serverfd, 0))
        DIE("Cannot start listening.");
    
    return serverfd;
}



void
handle (int serverfd, void (*handler)(int))
{
    int index = 0;
    struct pollfd rfds[FD_LIMIT];

    for (index = 0; index < FD_LIMIT; ++index)
    {
        rfds[index].fd     = -1;
        rfds[index].events = 0;
    }

    rfds[0].fd     = serverfd;
    rfds[0].events = POLLIN;

    while (1)
    {
        int clientfd;
        int retval;

        retval = poll(rfds, FD_LIMIT, 1000);
        if (-1 == retval)
            continue;

        for (index = 0; index < FD_LIMIT; ++index)
        {
            struct pollfd* current = &(rfds[index]);
            if (!(current->revents & POLLIN))
                continue;

            if (serverfd == current->fd)
            {
                init_client(serverfd, rfds);
                continue;
            }

            handler(current->fd);
            close_conn(current);
        }
    }
}

int
init_client(int serverfd, struct pollfd* rfds)
{
    int     index = 0;
    int     clientfd;
    char*   addr;
    unsigned int       client_siz;
    struct sockaddr_in client_addr;

    bzero(&client_addr, sizeof(struct sockaddr_in));

    clientfd = accept(serverfd, (struct sockaddr*)&client_addr, &client_siz);
    if (-1 == clientfd)
    {
        perror("Cannot accept client fd.");
        return -1;
    }

    for (index = 0; index < FD_LIMIT; ++index)
    {
        if (-1 != rfds[index].fd)
            continue;

        rfds[index].fd     = clientfd;
        rfds[index].events = POLLIN;

        printf("Fd %d has been held in keyhole %d.\n", clientfd, index);
        break;
    }

    if (FD_LIMIT == index)
    {
        perror("Maximum fd exceed.");
        return -1;
    }

    cast_ipaddress(&addr, client_addr);
    printf("Received connection from %s.\n", addr);

    free(addr);
    addr = NULL;

    return 0;
}


void
cast_ipaddress(char** addr, struct sockaddr_in client_addr)
{
    *addr = (char*)malloc(INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(client_addr.sin_addr), *addr, INET_ADDRSTRLEN);
}


void
close_conn(struct pollfd* item)
{
    shutdown(item->fd, SHUT_RDWR);
    printf("Fd %d disconnected.\n", item->fd);

    item->fd     = -1;
    item->events = 0;
}