# Ajouter ici les noms des programmes à compiler

all: tp2 tools.o serveur.o client.o clean

tp2: tp2.c tools.o serveur.o client.o
	gcc -o tp2 tools.o serveur.o client.o tp2.c

serveur.o: serveur.c
	gcc -c serveur.c

client.o: client.c
	gcc -c client.c

tools.o: tools.c
	gcc -c tools.c

clean:
	rm -f *~ *.o