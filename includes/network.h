#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>


#define PORT 8009
#define MAX_CONNECTION 100

typedef struct users_s users_t;

struct users_s
{
    int fd;
    char *name;
    struct users_s *next;
};

// display.c
void sendAll(users_t **list, int fd, char *input, char *username);

// initServer.c
int initServer(void);

// server.c
int startServer(int ServerFD);
int *getServerStatus(void);

// usersStruct.c
void pushBack(int fd, users_t **users);
void display(users_t *users);
void clearList(users_t *list);
void popClient(users_t **list, int fd);