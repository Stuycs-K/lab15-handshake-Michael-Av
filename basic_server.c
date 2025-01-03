#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;
  //printf("y u no work server\n");

  from_client = server_handshake( &to_client );

  int number;
  read(from_client, &number, sizeof(int));
  printf("number received: %d\n", number);

  number++;
  write(to_client, &number, sizeof(int));
}
