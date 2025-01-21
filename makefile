all: client server replay
client: clientop.o networker.o gamer.o
	@gcc -o client clientop.o networker.o gamer.o

server: serverop.o networker.o gamer.o
	@gcc -o server serverop.o networker.o gamer.o

replay: replay.o networker.o gamer.o
	@gcc -o replay replay.o networker.o gamer.o

clientop.o: clientop.c networker.h gamer.h
	@gcc -c clientop.c

serverop.o: serverop.c networker.h gamer.h
	@gcc -c serverop.c

replay.o: replay.c networker.h gamer.h
	@gcc -c replay.c

networker.o: networker.c networker.h
	@gcc -c networker.c networker.h

gamer.o: gamer.c gamer.h
	@gcc -c gamer.c gamer.h

clean:
	rm -rf *.o server client

runserver:
	@./server

runclient:
	@./client

runreplay:
	@./replay
