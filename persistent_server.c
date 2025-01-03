#include "pipe_networking.h"
#include <signal.h>

void sighandler(int signo){
  if (signo == SIGINT){
    remove(WKP);
    exit(0);
  }
}

int main() {
  int to_client;
  int from_client;
  //printf("y u no work server\n");

  while (1){
    from_client = server_handshake( &to_client );

    int number;
    int randfd = open("/dev/urandom", O_RDONLY);
    int readResult = read(randfd, &number, sizeof(int));
    if (readResult == -1) { printf("reading from random number failed\n"); exit(1);}

    printf("Sending %d to client(s)\n", number);

    while (1){
      sleep(1);
      write(to_client, &number, sizeof(int));
    }
}
