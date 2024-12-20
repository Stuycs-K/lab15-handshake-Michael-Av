#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  mkfifo(WKP, 0666);

  int fifoFD = open(WKP, O_RDONLY);
  printf("from_client fd: %d\n", fifoFD);

  remove(WKP);
  return fifoFD;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int x = 0;
  int * from_client = &x;
  *from_client = server_setup();

  char clientFifoPath[HANDSHAKE_BUFFER_SIZE + 1];
  printf("created pathj variable\n");
  int readResult = read(*from_client, clientFifoPath, HANDSHAKE_BUFFER_SIZE);
  if (readResult == -1){ printf("Server reading from WKP error\n"); exit(1);}
  printf("readResult: %d\n", readResult);

  *to_client = open(clientFifoPath, O_WRONLY);
  printf("to_client fd: %d\n", *to_client);

  return 0;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  // Opening PP
  int pid = getpid();
  int * from_server;

  // Making path for from_server
  char fifoPath[HANDSHAKE_BUFFER_SIZE];
  sprintf(fifoPath, "%d", pid);
  mkfifo(fifoPath, 0666);
  // for (int i = 0; i < strlen(fifoPath); i++){
  //   printf("%c\n", fifoPath[i]);
  // }

  // Opening WKP
  *to_server = open(WKP, O_WRONLY);
  printf("to_server fd: %d\n", *to_server);

  // Writing SYN
  int writeResult = write(*to_server, fifoPath, HANDSHAKE_BUFFER_SIZE);
  if (writeResult == -1){ printf("Client writing to WKP error\n"); exit(1);}
  printf("writeResult: %d\n", writeResult);

  // Opening PP to read from server
  *from_server = open(fifoPath, O_RDONLY);
  printf("from_server fd: %d\n", *from_server);

  remove(fifoPath);

  // Writing private pipe to WKP

  return 0;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}
