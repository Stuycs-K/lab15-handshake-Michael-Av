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
  printf("Server fifoFD: %d\n", fifoFD);

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
  int serverFifo = server_setup();
  int * clientPP;
  int readResult = read(serverFifo, clientPP, HANDSHAKE_BUFFER_SIZE);
  if (readResult == -1){ printf("Server reading from WKP error\n"); exit(1);}
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
  int fifoClient = open(getpid(), O_RDWR);
  printf("fifoClient fd: %d\n", fifoClient);

  // Opening WKP
  int fifoServer = open(WKP, O_WRONLY);
  printf("WKP fifo fd: %d\n", fifoServer);

  // Writing private pipe to WKP
  int writeResult = write(fifoServer, getpid(), HANDSHAKE_BUFFER_SIZE);
  if (writeResult == -1){ printf("Client writing to WKP error\n"); exit(1);}
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
