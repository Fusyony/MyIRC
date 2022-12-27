#include "network.h"
#include "glob.h"

void set_readFDS(fd_set *read_fds, int serverFD, users_t *list)
{
    users_t *ptr = list;

    FD_ZERO(read_fds);

    for (; ptr != 0 && ptr != 0; ptr = ptr->next) {
        FD_SET(ptr->fd, read_fds);
    }
    FD_SET(serverFD, read_fds);
}

int *getServerStatus(void)
{
    static int running = 1;

    return (&running);
}

char *readContent(int fd)
{
    char *buff = NULL;
    size_t len = 0;
    FILE *file = fdopen(fd, "r+");

    if (getline(&buff, &len, file) == -1) {
        if (ferror(file)) {
            printf("ERROR GETLINE: %s\n", strerror(errno));
            return (NULL);
        } else if (feof(file)) {
            return (NULL);
        }
    }
    buff[strlen(buff)-1] = 0; // remove newline character
    return (buff);
}

void manageInput(users_t **list, fd_set read_fds)
{
    users_t *ptr = *list;
    char *input = NULL;

    for (; ptr != NULL; ptr = ptr->next) {
        if (FD_ISSET(ptr->fd, &read_fds)) {
            input = readContent(ptr->fd);
            if (input == NULL) {
                popClient(list, ptr->fd);
            } else if (!ptr->name) {
                ptr->name = input;
                printf("[NEW USER] : %s\n", ptr->name);
                return; // return for cancel the free
            } else {
                printf("[%s]->%s\n",ptr->name, input);
                sendAll(list, ptr->fd, input, ptr->name);
            }
            break;
        }
    }
    free(input);
}

int startServer(int serverFD)
{
    socklen_t client = 0;
    struct sockaddr_in cli;
    fd_set read_fds;
    users_t *list = NULL;
    int newfd = 0;

    while (1) {
        set_readFDS(&read_fds, serverFD, list);
        select(MAX_CONNECTION, &read_fds, NULL, NULL, NULL);
        if (FD_ISSET(serverFD, &read_fds)) {
            newfd = accept(serverFD, (struct sockaddr *) &cli, &client);
            pushBack(newfd, &list);
            write(newfd, "Welcome to my IRC SERVER\n", 26);
            write(newfd, "Please Enter your username : ", 30);
        } else {
            manageInput(&list, read_fds);
        }
    }
    clearList(list);
    return (0);
}