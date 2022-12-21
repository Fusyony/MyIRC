#include "glob.h"
#include "error.h"

void putStr(char *message)
{
  write(1, message, strlen(message));
}

void displayError(char *message)
{
  perror(message);
  _exit(-1);
}
