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
#include "gamer.h"
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
  int to_client;
  int from_client;

  int shmd;
  int *data;
  shmd = shmget(SHMK,0,0);
  printf("SHM created: %d",shmd);
  data =shmat(shmd,0,0);

  while(1){
    int from_client = serverprep();
    to_client = serverconnect(from_client);
    }
}
