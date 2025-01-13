#include "gamer.h"

int coinflip(){
  return(rand()%2);
}

void serverStarts(int gamestate[5], int pipe){
  printf("Coinflip won! You go first.\n");
  serverTurn(gamestate, pipe);

}

void serverTurn(int gamestate[5], int pipe){
  char buffer[512];
  printf("Would you like to attack or split?\n");
  fgets(buffer,sizeof[buffer],stdin);
  if (strcmp("attack\n",buffer)==0){
    printf("With which hand would you like to attack?\n");
    fgets(buffer,sizeof[buffer],stdin);
    if (strcmp("1\n",buffer)==0){
      if(gamestate[0]==0){
        printf("Choose an active hand!\n");
      }
      else{
        printf("Which hand would you like to attack?\n");
        fgets(buffer,sizeof[buffer],stdin);
        if (strcmp("1\n",buffer)==0){ // Start of choosing target
          if(gamestate[2]==0){
            printf("Choose an active hand!\n");
          }
          else{
            sendcmd("atk",1,1);
          }
        }
        else if (strcmp("2\n",buffer)==0){
          if(gamestate[3]==0){
            printf("Choose an active hand!\n");
          }
          else{
            sendcmd("atk",1,2,pipe);
          }
        }//End of choosing target
      }
    }
    else if (strcmp("2\n",buffer)==0){
      if(gamestate[1]==0){
        printf("Choose an active hand!\n");
      }
      else{
        printf("Which hand would you like to attack?\n");
        fgets(buffer,sizeof[buffer],stdin);
        if (strcmp("1\n",buffer)==0){ // Start of choosing target
          if(gamestate[2]==0){
            printf("Choose an active hand!\n");
          }
          else{
            sendcmd("atk",2,1,pipe);
          }
        }
        else if (strcmp("2\n",buffer)==0){
          if(gamestate[3]==0){
            printf("Choose an active hand!\n");
          }
          else{
            sendcmd("atk",2,2,pipe);
          }
        }//End of choosing target
      }
    }
    else{
      printf("Invalid input. Enter 1 or 2.\n");
      serverTurn(gamestate,pipe);
    }
  }//end of "attack" code
  else if (strcmp("split\n",buffer)==0){
    printf("Which hand would you like to split with?\n");
    fgets(buffer,sizeof[buffer],stdin);
    if (strcmp("1\n",buffer)==0){
      if(gamestate[0]==0){
        printf("Choose an active hand!\n");
      }
      else(){
        printf("How many would you like to transfer?(1-%d)",gamestate[0]);
      }
    }


    }
  }
  else(){
    printf("invalid input. Please enter 'attack' or 'split'");
  }
}
