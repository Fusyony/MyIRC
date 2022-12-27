
// main file

#include "glob.h"
#include "network.h"

void closeServer(int signal)
{

  printf("TRY to kill the server\n");
  int *state = getServerStatus();

  printf("old state : %d", *state);

  *state = 0;
  signal = signal;

  printf("state : %d", *state);
}

int main(int argc, char **argv)
{

  // signal(SIGINT, closeServer);

  printf("argc : %d, argv : %s\n", argc, argv[0]);
  

  int socket = 0;

  

  socket = initServer();

  write(1, "[SERVER] : Server is UP\n", 25);

  startServer(socket);

  return (0);
}
