# Ajouter ici les noms des programmes à compiler

all: main tools.o serveur.o client.o clean

main: main.c tools.o serveur.o client.o
	gcc -o main tools.o serveur.o client.o main.c

serveur.o: serveur.c
	gcc -c serveur.c

client.o: client.c
	gcc -c client.c

tools.o: tools.c
	gcc -c tools.c

clean:
	rm -f *~ *.o
