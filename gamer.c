#include "gamer.h"

int coinflip(){
  return(rand()%2);
}

void serverStarts(struct gstate state, int pipe){
  printf("Coinflip won! You go first.\n");
  serverTurn(state, pipe);

}

void serverTurn(struct gstate state, int pipe){
  char buffer[512];
  struct move temp;
  printf("Would you like to attack or split?\n");
  fgets(buffer,sizeof(buffer),stdin);
  if (strcmp("attack\n",buffer)==0){
    printf("With which hand would you like to attack?\n");
    fgets(buffer,sizeof(buffer),stdin);
    if (strcmp("1\n",buffer)==0){
      if(state.h1==0){
        printf("Choose an active hand!\n");
      }
      else{
        printf("Which hand would you like to attack?\n");
        fgets(buffer,sizeof(buffer),stdin);
        if (strcmp("1\n",buffer)==0){ // Start of choosing target
          if(state.h3==0){
            printf("Choose an active hand!\n");
          }
          else{
            temp.type = "atk";
            temp.hand = 1;
            temp.target = 1;
            sendcmd(temp);
          }
        }
        else if (strcmp("2\n",buffer)==0){
          if(state.h4==0){
            printf("Choose an active hand!\n");
          }
          else{
            temp.type = "atk";
            temp.hand = 1;
            temp.target = 2;
            sendcmd(temp);
          }
        }//End of choosing target
      }
    }
    else if (strcmp("2\n",buffer)==0){
      if(state.h2==0){
        printf("Choose an active hand!\n");
      }
      else{
        printf("Which hand would you like to attack?\n");
        fgets(buffer,sizeof(buffer),stdin);
        if (strcmp("1\n",buffer)==0){ // Start of choosing target
          if(state.h3==0){
            printf("Choose an active hand!\n");
          }
          else{
            temp.type = "atk";
            temp.hand = 2;
            temp.target = 1;
            sendcmd(temp);
          }
        }
        else if (strcmp("2\n",buffer)==0){
          if(state.h4==0){
            printf("Choose an active hand!\n");
          }
          else{
            temp.type = "atk";
            temp.hand = 2;
            temp.target = 2;
            sendcmd(temp);
          }
        }//End of choosing target
      }
    }
    else{
      printf("Invalid input. Enter 1 or 2.\n");
      serverTurn(state,pipe);
    }
  }//end of "attack" code
  else if (strcmp("split\n",buffer)==0){ // SPLITTING LETS YOU STALL SWAP RN, NEED TO CHANGE.
    printf("Which hand would you like to split with?\n");
    fgets(buffer,sizeof(buffer),stdin);
    if (strcmp("1\n",buffer)==0){
      if(state.h1==0){
        printf("Choose an active hand!\n");
      }
      else{
        printf("How many would you like to transfer?(1-%d)",state.h1);
        fgets(buffer,sizeof(buffer),stdin);
        int nuMoved=0;
        sscanf(buffer,"%d",&nuMoved);
        if(nuMoved<1||nuMoved>state.h1){
          printf("enter a valid #(1-%d)",state.h1);
        }
        else{
          temp.type = "swp";
          temp.hand = 1;
          temp.howmuch = nuMoved;
        }
      }
    }
    else if(strcmp("2\n",buffer)==0){
      if(state.h2==0){
        printf("Choose an active hand!\n");
      }
      else{
        printf("How many would you like to transfer?(1-%d)",state.h2);
        fgets(buffer,sizeof(buffer),stdin);
        int nuMoved=0;
        sscanf(buffer,"%d",&nuMoved);
        if(nuMoved<1||nuMoved>state.h2){
          printf("enter a valid #(1-%d)",state.h2);
        }
        else{
          temp.type = "swp";
          temp.hand = 2;
          temp.howmuch = nuMoved;
        }
      }
    }
    else{
      printf("Invalid input. Enter 1 or 2.\n");
      serverTurn(state,pipe);
    }
  }
  else{
    printf("invalid input. Please enter 'attack' or 'split'");
    serverTurn(state, pipe);
  }
} // Client's program should be the same, but swap the h1 and h3 and h2 and h4
