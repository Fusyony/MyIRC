#include "network.h"
#include "glob.h"

users_t *createNode(void)
{
    users_t *users = malloc(sizeof(users_t));

    users->fd = 0;
    users->next = NULL;
    users->name = NULL;
    return (users);
}

void pushBack(int fd, users_t **users)
{
    users_t *tmp = *users;
    users_t *newNode = createNode();

    newNode->fd = fd;
    if (tmp == 0)
        *users = newNode;
    else {
        for (; tmp->next != 0; tmp = tmp->next);
        tmp->next = newNode;
    }
}

void clearList(users_t *list)
{
    users_t *ptr = list;  
    users_t *clear = ptr;

    while (ptr) {
        clear = ptr;
        ptr = ptr->next;
        free(clear);
    }
}

void popClient(users_t **users, int fd) // remove client with the coresponding FD
{
    users_t *prev = *users;
    users_t *toRemove = *users;

    if (toRemove->fd == fd) {
        prev = toRemove->next;
        close(toRemove->fd);
        free(toRemove);
        (*users) = prev;
        return;
    }
    if (toRemove->next) {
        toRemove = toRemove->next;
    } else {
        return; // wrong FD or ERROR
    }
    for (;  toRemove != NULL && toRemove->fd != fd; toRemove = toRemove->next, prev = prev->next);
    if (toRemove) {
        prev->next = toRemove->next;
        close(toRemove->fd);
        free(toRemove);
    }
}

void display(users_t *users)
{
    users_t *tmp = users;

    for (; tmp != 0; tmp = tmp->next) {
        printf("[USER] FD : %d\n", tmp->fd);  
    }
}