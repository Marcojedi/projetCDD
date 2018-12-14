#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

#include "global.h"
#include "tools.h"

/**
    @encode pgme
*/
char encode(char msg){
    typedef unsigned char octet_t;
}

/**
    @return ascii code from a char c
*/
int ascii_code(char c){ 
	return c;
}

void serveur(char *src,int pipefd[2] ) {
    char * mots[3840];
  int i=0,nb_mot;
  char buf[BUFSIZ]; char m;
	static octet_t * Triplet = NULL;
	if(!Triplet) Triplet = (octet_t*) malloc(3*sizeof(octet_t));

  close( pipefd[0] );		// Close unused read end
  FILE * fd;
  fd = fopen(src,"r");
	if(fd==NULL) perror("Erreur ouverture, fichier introuvable"); 
  while(fgets(buf,BUFSIZ,fd)!=NULL){
		while(buf[i]!='\n'){ //Recupère chaque lettre
				m = buf[i];
				write( pipefd[1], &m , 1 );
				i++;
		}
		i=0;
    }

    printf("le serveur ferme\n\n");
    close(pipefd[1]); // Reader will see EOF
    wait(NULL); // Wait for child
    exit(EXIT_SUCCESS);
}




