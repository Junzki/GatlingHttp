#include "asset.h"
#include "socket.h"
#include "http.h"

int
main(int argc, const char * argv[]) {
    int server = init_server(9001);
    handle(server, http_handler);
    return 0;
}
