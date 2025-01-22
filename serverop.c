#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "networker.h"

//This one will manage the server, facilitating it to keep accepting clients
//catches signals

static void sighandler(int signo){
  if(signo==SIGINT){
    printf("SIGINT caught, exiting\n");
    unlink(WKP);
    exit(0);
  }
}

int main() {
  signal(SIGINT,sighandler);
  signal(SIGPIPE, SIG_IGN);
  srand(time(NULL));
  int to_client;
  int from_client;

  while(1){
    from_client = serverprep();
    to_client = serverconnect(from_client);
  }
}
