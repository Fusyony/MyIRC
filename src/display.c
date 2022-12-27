#include "glob.h"
#include "error.h"
#include "network.h"

void putStr(char *message)
{
  write(1, message, strlen(message));
}

void displayError(char *message)
{
  perror(message);
  _exit(-1);
}

void sendAll(users_t **list, int fd, char *input, char *username)
{
  users_t *ptr = *list;

  for (; ptr != NULL; ptr = ptr->next) {
    if (ptr->fd == fd)
      continue;
    write(ptr->fd, "[", 1);
    write(ptr->fd, username, strlen(username));
    write(ptr->fd, "]->", 3);
    write(ptr->fd, input, strlen(input));
    write(ptr->fd, "\n", 2);
  }
}