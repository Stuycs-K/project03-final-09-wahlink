#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <termios.h>
#include "networker.h"
#include "gamer.h"
#define DATA "datafiler3123"

void clean_stdin(){
  int stdin_copy = dup(STDIN_FILENO);
  tcdrain(stdin_copy);
  tcflush(stdin_copy, TCIFLUSH);
  close(stdin_copy);
}

static void sighandler(int signo){
  if(signo==SIGINT){
    printf("SIGINT caught, exiting\n");
    unlink(WKP);
    exit(0);
  }
}


int playturn(int fd){
  int servPlay;
  int cliPlay;
  if(read(fd, &servPlay,sizeof(servPlay))<=0){
    printf("This round does not exist. Resetting to round 1.\n");
    lseek(fd,0,SEEK_SET);
    return -1;
  }
  read(fd,&cliPlay,sizeof(cliPlay));
  char* m; m = (char*)malloc(10);
  char* t; t = (char*)malloc(10);
  if(servPlay==0){
    strcpy(m,"rock");
  }
  if(servPlay==2){
    strcpy(m,"scissors");
  }
  if(servPlay == 1){
    strcpy(m,"paper");
  }
  if(cliPlay==0){
    strcpy(t,"rock");
  }
  if(cliPlay==2){
    strcpy(t,"scissors");
  }
  if(cliPlay == 1){
    strcpy(t,"paper");
  }
  printf("Server played %s, client played %s\n",t,m);
  free(m);
  free(t);
  if(checkVictory(servPlay,cliPlay)!=-1){
    if(checkVictory(servPlay,cliPlay)==0){
      printf("Client Won!\n");

    }
    else{
      printf("Server Won!\n");

    }
  }
  else{
    printf("Draw.\n");
  }
  return 0;
}//print one rond

int main(){
  signal(SIGINT,sighandler);
  printf("Type 'play' to replay all rounds, or type l and r to navigate the rounds\n");
  char buffer[5];
  int fd = open(DATA,O_RDONLY,0666);
  if(fd==-1){
    printf("File opening failed.\n");
    exit(0);
  }
  int turn = 1;
  while(fgets(buffer,sizeof(buffer),stdin)){
    clean_stdin();
    if(strcmp(buffer,"play")==0){
      printf("Turn %d:\n",turn);
      lseek(fd,+2*sizeof(int),SEEK_SET);
      while(playturn(fd)!=-1){
        turn++;
        printf("Turn %d:\n",turn);
        lseek(fd,+2*sizeof(int),SEEK_CUR);
      }
      lseek(fd,+2*sizeof(int),SEEK_SET);
      turn =1;
      clean_stdin();
      strcpy(buffer,"");
      continue;
    }
    else if(strcmp(buffer,"l\n")==0){
      if(turn>1){
        turn--;
        printf("Turn %d:\n",turn);
        lseek(fd,-4*sizeof(int),SEEK_CUR);
        playturn(fd);
        lseek(fd,-2*sizeof(int),SEEK_CUR);
      }
      else{
        printf("Can't go any lower!\n");
      }
    }
    else if(strcmp(buffer,"r\n")==0){
      turn++;
      printf("Turn %d:\n",turn);
      lseek(fd,+4*sizeof(int),SEEK_CUR);
      if(playturn(fd)==-1){
        turn=0;
      }
      else{
        lseek(fd,-2*sizeof(int),SEEK_CUR);
      }
    }
    else{
      printf("Enter an input - 'play, 'l', or 'r'\n");
    }
    clean_stdin();
    printf("Type 'play' to replay all rounds, or type l and r to navigate the rounds. Awaiting input:\n");
  }

  return 0;
}
