#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "networker.h"
#include "gamer.h"
//This one will manage the server, facilitating it to keep accepting clients
//catches signals
