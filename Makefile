# Ajouter ici les noms des programmes à compiler

all: main serveur.o client.o clean

main: main.c serveur.o client.o
	gcc -o main serveur.o client.o main.c

serveur.o: serveur.c
	gcc -c serveur.c

client.o: client.c
	gcc -c client.c

clean:
	rm -f *~ *.o
