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
//This one will handle the client, probably only catching signals

static void sighandler(int signo){
  if(signo==SIGINT){
    printf("SIGINT caught, exiting\n");
    exit(0);
  }
}

int main(){
  signal(SIGINT,sighandler);
  int to_server;
  int from_server;

  from_server = clientconnect( &to_server );
  return 0;
}
