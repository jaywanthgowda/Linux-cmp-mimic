output:server.o client.o
	gcc -o output server.o client.o
server.o:server.c interface.h
	gcc -c server.c
client.o:client.c interface.h
	gcc -c client.c
clean:
		rm server.o client.o
