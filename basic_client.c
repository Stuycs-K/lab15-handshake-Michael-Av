#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;
  //printf("y u no work client\n");

  from_server = client_handshake( &to_server );

  int newNumber;
  while (1){
    read(from_server, &newNumber, sizeof(int));
    printf("%d\n", newNumber);
  }

}
