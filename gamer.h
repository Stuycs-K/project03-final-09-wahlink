#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#ifndef GAMER_H
#define GAMER_H
int coinflip();
void serverStarts(int gamestate[5], int pipe);
void serverTurn(int gamestate[5], int pipe);
void sendcmd(struct move play);
struct gstate{
  int Player;
  int h1;
  int h2;
  int h3;
  int h4;
} gstate;

struct move{
  char type;
  int hand;
  int target;
  int howmuch;
} move;

#endif
