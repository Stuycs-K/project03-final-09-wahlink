all: client server
client: clientop.o networker.o gamer.o
	gcc -o client clientop.o networker.o gamer.o

server: serverop.o networker.o gamer.o
	gcc -o server serverop.o networker.o gamer.o

clientop.o: clientop.c networker.h gamer.h
	gcc -c clientop.c

serverop.o: serverop.c networker.h gamer.h
	gcc -c serverop.c

networker.o: networker.c networker.h
	gcc -c networker.c networker.h

gamer.o: gamer.c gamer.h
	gcc -c gamer.c gamer.h
