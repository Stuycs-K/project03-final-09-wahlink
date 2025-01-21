#include "gamer.h"

int coinflip(){
  return(rand()%2);
}

struct move serverStarts(struct gstate state){
  printf("Coinflip won! You go first.\n");
  return serverTurn(state);
}

struct move clientStarts(struct gstate state){
  printf("Coinflip won! You go first.\n");
  return clientTurn(state);
}

void sendcmd(struct move play, int pipe){
  write(pipe, &play, sizeof(&play));
}

int checkVictory(struct gstate state){//Returns: 0 on serverWin, 1 on clientWin, -1 on neither
  if(state.h1==0&&state.h2==0){
    return 1;
  }
  if(state.h3 == 0&&state.h4==0){
    return 0;
  }
  return -1;
}

struct gstate newStateServ(struct gstate state, struct move play){ // Takes a move struct and uses it to create a new state struct for replay.
  struct gstate temp;
  temp.h1 = state.h1;
  temp.h2 = state.h2;
  temp.h3 = state.h3;
  temp.h4 = state.h4;
  temp.player = (state.player-1)*-1
  if(state.player==0){
    if (play.type == "atk"){
      if(play.hand == 1){
        if (play.target==1){
          temp.h3 += temp.h1;
        }
        else if(play.target ==2){
          temp.h4+=temp.h1;
        }
      }
      else if (play.hand ==2){
        if (play.target==1){
          temp.h3 += temp.h2;
        }
        else if(play.target ==2){
          temp.h4+=temp.h2;
        }
      }//hand2
    }//attacks
    else if(play.type == "swp"){
      if(play.hand == 1){
        temp.h2 += play.howmuch;
      }//hand1
      else if (play.hand ==2){
        temp.h1 += play.howmuch;
      }//hand2
    }//swapping
  }//SERVER TURN PROCESSER
  else if(state.player==1){

  }
  return temp;
}

void logTurn(struct packg packet, int fd){//MUST BE COMPLETED MUST BE COMPLETED MUST BE COMPLETED
  write(fd, &packet, sizeof(&packet));
}

struct move serverTurn(struct gstate state){
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
            return temp;
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
            return temp;
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
            return temp;
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
            return temp;
          }
        }//End of choosing target
      }
    }
    else{
      printf("Invalid input. Enter 1 or 2.\n");
      serverTurn(state);
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
      serverTurn(state);
    }
  }
  else{
    printf("invalid input. Please enter 'attack' or 'split'");
    serverTurn(state, pipe);
  }
} // Client's program should be the same, but swap the h1 and h3 and h2 and h4

struct move clientTurn(struct gstate state){
  char buffer[512];
  struct move temp;
  printf("Would you like to attack or split?\n");
  fgets(buffer,sizeof(buffer),stdin);
  if (strcmp("attack\n",buffer)==0){
    printf("With which hand would you like to attack?\n");
    fgets(buffer,sizeof(buffer),stdin);
    if (strcmp("1\n",buffer)==0){
      if(state.h4==0){
        printf("Choose an active hand!\n");
      }
      else{
        printf("Which hand would you like to attack?\n");
        fgets(buffer,sizeof(buffer),stdin);
        if (strcmp("1\n",buffer)==0){ // Start of choosing target
          if(state.h1==0){
            printf("Choose an active hand!\n");
          }
          else{
            temp.type = "atk";
            temp.hand = 1;
            temp.target = 1;
            return temp;
          }
        }
        else if (strcmp("2\n",buffer)==0){
          if(state.h2==0){
            printf("Choose an active hand!\n");
          }
          else{
            temp.type = "atk";
            temp.hand = 1;
            temp.target = 1;
            return temp;
          }
        }//End of choosing target
      }
    }
    else if (strcmp("2\n",buffer)==0){
      if(state.h4==0){
        printf("Choose an active hand!\n");
      }
      else{
        printf("Which hand would you like to attack?\n");
        fgets(buffer,sizeof(buffer),stdin);
        if (strcmp("1\n",buffer)==0){ // Start of choosing target
          if(state.h1==0){
            printf("Choose an active hand!\n");
          }
          else{
            temp.type = "atk";
            temp.hand = 2;
            temp.target = 1;
            return temp;
          }
        }
        else if (strcmp("2\n",buffer)==0){
          if(state.h2==0){
            printf("Choose an active hand!\n");
          }
          else{
            temp.type = "atk";
            temp.hand = 2;
            temp.target = 2;
            return temp;
          }
        }//End of choosing target
      }
    }
    else{
      printf("Invalid input. Enter 1 or 2.\n");
      clientTurn(state);
    }
  }//end of "attack" code
  else if (strcmp("split\n",buffer)==0){ // SPLITTING LETS YOU STALL SWAP RN, NEED TO CHANGE.
    printf("Which hand would you like to split with?\n");
    fgets(buffer,sizeof(buffer),stdin);
    if (strcmp("1\n",buffer)==0){
      if(state.h3==0){
        printf("Choose an active hand!\n");
      }
      else{
        printf("How many would you like to transfer?(1-%d)",state.h3);
        fgets(buffer,sizeof(buffer),stdin);
        int nuMoved=0;
        sscanf(buffer,"%d",&nuMoved);
        if(nuMoved<1||nuMoved>state.h3){
          printf("enter a valid #(1-%d)",state.h3);
        }
        else{
          temp.type = "swp";
          temp.hand = 1;
          temp.howmuch = nuMoved;
        }
      }
    }
    else if(strcmp("2\n",buffer)==0){
      if(state.h4==0){
        printf("Choose an active hand!\n");
      }
      else{
        printf("How many would you like to transfer?(1-%d)",state.h4);
        fgets(buffer,sizeof(buffer),stdin);
        int nuMoved=0;
        sscanf(buffer,"%d",&nuMoved);
        if(nuMoved<1||nuMoved>state.h4){
          printf("enter a valid #(1-%d)",state.h4);
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
      clientTurn(state);
    }
  }
  else{
    printf("invalid input. Please enter 'attack' or 'split'");
    clientTurn(state);
  }
} // ClientTurn
