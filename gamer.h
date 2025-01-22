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


int checkDeath(int inpt);
void printstage(int mine, int theirs);
int checkVictory(int mine, int theirs);

#endif
