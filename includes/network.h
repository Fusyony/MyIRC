#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

#define PORT 3516
#define MAX_CONNECTION 100

int initServer(void);
int startServer(int ServerFD);

