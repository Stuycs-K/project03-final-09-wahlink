#include "gamer.h"

int coinflip(){
  return(rand()%2);
}



void printstage(int mine, int theirs){
  char* m; m = (char*)malloc(10);
  char* t; t = (char*)malloc(10);
  if(mine==0){
    strcpy(m,"rock");
  }
  if(mine==2){
    strcpy(m,"scissors");
  }
  if(mine == 1){
    strcpy(m,"paper");
  }
  if(theirs==0){
    strcpy(t,"rock");
  }
  if(theirs==2){
    strcpy(t,"scissors");
  }
  if(theirs == 1){
    strcpy(t,"paper");
  }
  printf("You played %s, they played %s\n",m,t);
  free(m);
  free(t);
}



int checkVictory(int mine, int theirs){//Returns: 0 on serverWin, 1 on clientWin, -1 on neither
  if(mine==theirs){
    return -1;
  }
  else if(mine+1==theirs||(mine-2) == theirs){
    return 1;
  }
  else{
    return 0;
  }
}

int checkDeath(int inpt){
  if(inpt>=5){
    return 0;
  }
  return inpt;
}
