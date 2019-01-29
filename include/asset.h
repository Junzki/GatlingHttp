#ifndef GHD_ASSET_H_
#define GHD_ASSET_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DIE(message)                                          \
do                                                            \
{                                                             \
    char errmsg[BUFSIZ];                                      \
    sprintf(errmsg, "%s:%d %s", __FILE__, __LINE__, message); \
    perror(errmsg);                                           \
    exit(EXIT_FAILURE);                                       \
} while(0);                                                   \

#define FD_LIMIT 128

#endif  /* GHD_ASSET_H_ */