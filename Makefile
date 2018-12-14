# Ajouter ici les noms des programmes à compiler

all: main LZW.o tools.o serveur.o client.o clean

main: main.c LZW.o tools.o serveur.o client.o
	gcc -o main LZW.o tools.o serveur.o client.o main.c

LZW.o: LZW.c
	gcc -c LZW.c

serveur.o: serveur.c
	gcc -c serveur.c

client.o: client.c
	gcc -c client.c

tools.o: tools.c
	gcc -c tools.c

clean:
	rm -f *~ *.o
