#include "networker.h"
#include "gamer.h"
//This one will hold all of the networking files and use gamers.c
//to access stdin and out for the actual game


int serverprep() {
  int from_client = 0;
  mkfifo(WKP,0666);
  int fifofd = open(WKP, O_RDONLY);
  from_client = fifofd;
  unlink(WKP);
  return from_client;
}

int clientconnect(int *to_server) {
  printf("Client start\n");
  int from_server;
  int griddy;
  griddy = getpid();
  printf("PID gotten\n");
  char fiddy[12];
  sprintf(fiddy, "%d",griddy);
  printf("pid converted\n");
  mkfifo(fiddy,0666);
  printf("PP created\n");
  int fifofd = open(WKP, O_WRONLY); //FIFOFD IS WKP HERE
  write(fifofd, &griddy,sizeof(griddy));
  printf("Client wrote %d via WKP\n",griddy);//WIP - SEND STRING PID AN JUST USE THAT BRO
  int wrfd = open(fiddy,O_RDONLY);//OPEN THE PP
  unlink(fiddy);
  int synack;
  read(wrfd,&synack,sizeof(synack));
  printf("client read %d via PP\n",synack);
  int ack = synack + 1;
  write(fifofd, &ack,sizeof(ack));
  printf("client wrote %d\n",ack);
  int x;
  while(read(wrfd, &x,sizeof(x))>0){
    printf("client read: %d\n",x);
    sleep(1);
  }
  return from_server;
}

int serverconnect(int from_client) {
  printf("fork starting up\n");
  int to_client  = 0;
  int piddler;
  char fiddler[12];
  read(from_client,&piddler,sizeof(piddler));//NEEDS TO USE FIDDLER FOR THE READ TARGET MY GUYS
  printf("Server reads %d via WKP\n",piddler);
  int childPID = piddler;
  sprintf(fiddler, "%d",piddler);
  int fifofd = open(fiddler,O_WRONLY);
  int synack = piddler+1;
  to_client = fifofd;
  write(fifofd, &synack,sizeof(synack)); // synack is the return value(PID + 1)
  printf("server wrote %d via PP\n",synack);
  read(from_client,&piddler,sizeof(piddler)); //Uses same "PIDDLER" var for all reads
  printf("server read %d. Connection complete.\n",piddler);
  //CONNECTION DONE MAKE THE GAME DOWN HERE
  int player; //0 MEANS IT IS SERVERS TURN, 1 MEANS CLIENTS TURN
  player = coinflip();
  int logFd;
  logFd = open(DATA,O_CREAT|O_RDWR|O_EXCL,0666);
  if(logFd == -1){ // REMEMBER TO CLOSE LOGFD
    printf("failed to open datafile. please delete it.\n");
  }//SAVE THE DATA RECALL FUNC FOR LATER JUST MAKE THE THING, MAKE SURE TO STORE GAMESTATES + TURN, AND FOCUS ON PIPING
  char buffer[5] = {1,1,1,1,player}; // First two are server's 'hands', second two are client's 'hands', last is current player
  write(logFd, buffer, sizeof(buffer));
  if(player==0){
    serverStarts(to_client);
  }

  int x = rand() % 100;
  while(write(fifofd, &x,sizeof(x))!=-1){
    printf("Server wrote %d\n",x);
    x = rand() % 100;
    sleep(1);
  }
  close(from_client);
  close(to_client);
  printf("connection closed with %d\n",childPID);
  return to_client;
}
