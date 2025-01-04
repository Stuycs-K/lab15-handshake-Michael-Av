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
  printf("parent pid: %d\n", getpid());

  while (1){
    printf("[%d] awaiting next client:\n", getpid());
    from_client = server_setup();
    signed int forkResult = fork();
    if (!forkResult){
      to_client = subserver_connect( from_client );

      int number;
      int randfd = open("/dev/urandom", O_RDONLY);
      int readResult = read(randfd, &number, sizeof(int));
      if (readResult == -1) { printf("reading from random number failed\n"); exit(1);}

      number %= 100;
      printf("[%d] Sending %d to client(s)\n", getpid(), number);

      while (1){
        sleep(1);
        int writeResult = write(to_client, &number, sizeof(int));
        if (writeResult == -1) { printf("Client closed connection."); break;}
      }
      close(from_client);
      close(to_client);
      exit(0);
    }
  }
}
