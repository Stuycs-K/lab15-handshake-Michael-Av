#include "pipe_networking.h"
#include <signal.h>

static void sighandler(int signo){
  if (signo == SIGINT){
    remove(WKP);
    exit(0);
  }
  if (signo == SIGPIPE){}
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGPIPE, sighandler);
  int to_client;
  int from_client;
  //printf("y u no work server\n");
    printf("Awaiting first client:\n");

  while (1){
    from_client = server_handshake( &to_client );

    int number;
    int randfd = open("/dev/urandom", O_RDONLY);
    int readResult = read(randfd, &number, sizeof(int));
    if (readResult == -1) { printf("reading from random number failed\n"); exit(1);}

    number %= 100;
    printf("Sending %d to client(s)\n", number);

    while (1){
      sleep(1);
      printf("here\n");
      int writeResult = write(to_client, &number, sizeof(int));
      if (writeResult == -1) { printf("Client closed connection. Awaiting next client\n"); break;}
    }
    close(from_client);
    close(to_client);
  }
}
