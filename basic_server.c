#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;
  //printf("y u no work server\n");

  from_client = server_handshake( &to_client );

  int number;
  int randfd = open("/dev/urandom", O_RDONLY);
  int readResult = read(randfd, &number, sizeof(int));
  if (readResult == -1) { printf("reading from random number failed\n"); exit(1);}

  printf("random number: %d\n", number);

  while (1){
    sleep(1);
    write(to_client, &number, sizeof(int));
  }
}
