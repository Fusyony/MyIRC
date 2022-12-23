#include "network.h"
#include "glob.h"


void set_readFDS(fd_set *read_fds, int serverFD)
{
    FD_ZERO(read_fds);

    FD_SET(serverFD, read_fds);
}

int startServer(int serverFD)
{
    socklen_t client = 0;
    struct sockaddr_in cli;
    int runing = 1;
    fd_set read_fds;

    set_readFDS(&read_fds, serverFD);

    while (runing) {
        select(MAX_CONNECTION, &read_fds, 0, 0, 0);
        int clientSocket = accept(serverFD, (struct sockaddr *) &cli, &client);

        write(clientSocket, "Hello world", 12);
    }

    return (0);
}