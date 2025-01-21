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
  struct gstate state;
  struct move play;
  struct packg packet;
  read(wrfd,&state,sizeof(&state));
  if(state.Player == 0){
    printf("Server plays first. Awaiting server turn...\n");
  }
  else if(state.Player == 1){
    play = clientStarts(state);
    state = newState(state,play);
  }
  while(read(wrfd, &packet,sizeof(packet))>0){
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
  struct gstate *startState=malloc(sizeof(gstate)); // First two are server's 'hands', second two are client's 'hands', last is current player
  startState->h1 = 1; startState->h2 = 1; startState->h3 = 1; startState->h4 = 1; startState->Player = player;
  write(logFd, startState, sizeof(startState));
  struct gstate state;//Var used for GAMESTATE
  state.h1 = 1; state.h2 = 1; state.h3 = 1; state.h4 = 1; state.Player = player;
  struct move play;//var used for MOVES MADE
  struct packg packet;
  if(player==0){
    play = serverStarts(*startState);
    state = newState(state, play);
    packet.play = play; packet.move = state;
  }
  while(write(fifofd, &packet,sizeof(&packet))!=-1){
    logTurn(packet,logFd);//LOG SERVER TURN
    if(checkVictory(state)!=-1){
      if(checkVictory(state)==0){
        printf("You Win!\n");
        break;
      }
      else{
        printf("You Lose!\n");
        break;
      }
    }
    if(read(from_client, &packet,sizeof(&packet))==-1){
      printf("Pipe connection closed, read failed.");
      break;
    }
    logTurn(packet,logFd);//LOG CLIENT TURN

    play = serverTurn(state);
    state = newState(state, play);
    packet.play = play; packet.move = state;
  }//Gameplay loop done I hope. Betas mogged.
  close(from_client);
  close(to_client);
  printf("connection closed with %d\n",childPID);
  return to_client;
}
