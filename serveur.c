#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

#include "global.h"
#include "tools.h"

/**
   @brief programme serveur
 */

int ascii_code(char c){ 
	return c;
}


void serveur( int pipefd[2] ) {
	
  int i=0;
  char buf[BUFSIZ];
	int intATransmettre;
  char * Id = (char*) calloc( 10, sizeof(char) );
  close( pipefd[0] );		// Close unused read end
  FILE * fd;
  fd = fopen("number.txt","r");
  while(fgets(buf,BUFSIZ,fd)!=NULL){
		while(buf[i]!='\n'){
			intATransmettre = ascii_code(buf[i]);	
			write( pipefd[1], &intATransmettre , 1 );//int bien transmis mais que sur 8 bits si intATransmettre > 255 ==> le nombre ecrit ne seraOK
			i++;
		}
		i=0;
  }

  printf("le serveur ferme\n\n");
  close(pipefd[1]); // Reader will see EOF
  wait(NULL); // Wait for child
  exit(EXIT_SUCCESS);
}




