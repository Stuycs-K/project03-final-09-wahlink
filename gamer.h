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
#include <sys/types.h>// might need gamer.h do that if it dont work

#ifndef GAMER_H
#define GAMER_H
int coinflip();
void serverStarts(int gamestate[5], int pipe);
void serverTurn(int gamestate[5], int pipe);
#endif
