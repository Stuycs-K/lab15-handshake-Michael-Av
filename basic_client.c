#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;
  //printf("y u no work client\n");

  from_server = client_handshake( &to_server );

  int number = 12;
  write(to_server, &number, sizeof(int));

  int newNumber;
  read(from_server, &newNumber, sizeof(int));
  if (newNumber == number + 1){
    printf("success\n");
  }
  else {
    printf("failure\n");
  }

}
