
// main file

#include "glob.h"
#include "network.h"

int main(int argc, char **argv)
{
  printf("argc : %d, argv : %s\n", argc, argv[0]);
  

  int socket = 0;

  printf("Starting Server");
  

  socket = initServer();

  printf("SOcket is : %d\n", socket);

  return (0);
}
