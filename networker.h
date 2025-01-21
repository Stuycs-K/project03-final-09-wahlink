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

#ifndef NETWORKER_H
#define NETWORKER_H
#define WKP "kaicenatsigmarizzohioskibidimonster"
//#define SHMK "choppedchinwheredoIevenStart" not using for 2p
#define DATA "shawtyslikeamelodyinmyhead"


int serverconnect(int from_client, FILE* rep);

int clientconnect(int *to_server);

int serverprep();

FILE* moreprep();


#endif
