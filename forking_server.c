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

      char line[BUFFER_SIZE];

      while (1){
        int readResult = read(from_client, line, BUFFER_SIZE);
        if (readResult == -1) { printf("reading from client string failed\n"); exit(1);}
        //Do something to line
        int writeResult = write(to_client, line, BUFFER_SIZE);
        if (writeResult == -1) { printf("Client closed connection.\n"); break;}
        sleep(1);
      }
      close(from_client);
      close(to_client);
      exit(0);
    }
  }
}
