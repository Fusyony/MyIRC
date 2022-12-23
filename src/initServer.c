
#include "network.h"
#include "glob.h"
#include "error.h"

int initServer(void)
{
  int socketFD = 0;
  struct sockaddr_in server;


  socketFD = socket(AF_INET, SOCK_STREAM, 0);

  if (socketFD < 0) {
    displayError("Error on socket creation");
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;


  if (bind(socketFD, (struct sockaddr *) &server, sizeof(server)) < 0) {
    displayError("Error on binding");
  }


  listen(socketFD, MAX_CONNECTION);

  return (socketFD);

}
