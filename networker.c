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
  printf("client wrote %d\n",ack); //3 WAY HANDSHAKE DONE
  int mine = 0;
  int theirs = 0;
  char buffer[10];
  printf("Make your move. Type 0 for rock, 1 for paper, and 2 for scissors\n");
  while(fgets(buffer,sizeof(buffer),stdin)!=NULL){
    if(sscanf(buffer,"%d",&mine)!= 1){
      printf("Enter a valid number!(0,1, or 2)\n");
      continue;
    }
    if(read(wrfd,&theirs,sizeof(theirs))==-1){
      printf("connection closed\n");
      break;
    }
    if(write(fifofd,&mine,sizeof(mine))==-1){
      printf("connection closed\n");
      break;
    }
    printf("You have played.");
    printstage(mine,theirs);
    if(checkVictory(mine,theirs)!=-1){
      if(checkVictory(mine,theirs)==0){
        printf("You Win!\n");

      }
      else{
        printf("You Lose!\n");

      }
    }
    else{
      printf("Draw.\n");
    }
    printf("Make your move. Type 0 for rock, 1 for paper, and 2 for scissors\n");
  }
  printf("Connection closed.\n");
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
  int mine = 0;
  int theirs = 0;
  int ours[2];
  char buffer[10];
  player = coinflip();
  int logFd;
  remove(DATA);
  logFd = open(DATA,O_CREAT|O_RDWR|O_EXCL,0666);
  if(logFd == -1){ // REMEMBER TO CLOSE LOGFD
    printf("failed to open datafile. please delete it.\n");
  }
  printf("Make your move. Type 0 for rock, 1 for paper, and 2 for scissors\n");
  while(fgets(buffer,sizeof(buffer),stdin)!=NULL){
    if(sscanf(buffer,"%d",&mine)!= 1){
      printf("Enter a valid number!(0,1, or 2)\n");
      continue;
    }
    if(write(fifofd,&mine,sizeof(theirs))==-1){
      printf("connection closed\n");
      break;
    }
    if(read(from_client,&theirs,sizeof(mine))==-1){
      printf("connection closed\n");
      break;
    }
    write(logFd,&mine,sizeof(&mine));
    write(logFd,&theirs,sizeof(&theirs));
    printf("Round complete. ");
    printstage(mine,theirs);
    if(checkVictory(mine,theirs)!=-1){
      if(checkVictory(mine,theirs)==0){
        printf("You Win!\n");

      }
      else{
        printf("You Lose!\n");

      }
    }
    else{
      printf("Draw.\n");
    }
    printf("Make your move. Type 0 for rock, 1 for paper, and 2 for scissors\n");
  }//Gameplay loop done I hope.

  close(logFd);
  close(from_client);
  close(to_client);
  printf("connection closed with %d\n",childPID);
  return to_client;
}
