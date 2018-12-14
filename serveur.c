#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

#include "global.h"
#include "tools.h"
#include "LZW.h"


/**
    @return ascii code from a char c
*/
int ascii_code(char c){ 
	return c;
}

void serveur(char *src,int pipefd[2] ) {
  /*char * mots[3840];
  int i=0,nb_mot;
  char buf[BUFSIZ]; char m;

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
  exit(EXIT_SUCCESS);*/

  byte_t Dn, Mn, c1 , c2 , c3;
  const int N = 3;
  char buf[BUFSIZ];
  int intATransmettre;
  char * Id = (char*) calloc( 10, sizeof(char) );
  
  close( pipefd[0] );    // Close unused read end
 
  int i, fd = open(src, O_RDONLY);
  if(fd==-1) perror("Erreur ouverture, fichier introuvable"); 


  //-------------------------
  struct stat st;
  fstat(fd, &st);
 
  byte *in = _new(char, st.st_size);
  read(fd, in, st.st_size);
  _setsize(in, st.st_size);
  close(fd);

  printf("input size:   %d\n", _len(in));
 
  byte *enc = lzw_encode(in, 9);
  printf("encoded size: %d\n", _len(enc));
  //ne pas oublier de CRYPTER !!
  //------------------------

  write( pipefd[1], &enc, 1 );

  printf("le serveur ferme\n\n");
  close(pipefd[1]); // Reader will see EOF
  wait(NULL); // Wait for child

  _del(in);
  _del(enc);

  exit(EXIT_SUCCESS);
}




