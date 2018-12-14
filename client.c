#include "stdlib.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

#include "global.h"
#include "tools.h"

/**
 * @brief le client lit les octet(signed char) que le serveur lui
 * envoie et les affiche.
 */
void client(char * dest, int pipefd[2] ) {	
  byte_t Oc;
  int buf;
  char * Id = (char *) calloc( 10, sizeof(char) );
	
  close(pipefd[1]);          // Close unused write end
  while (read(pipefd[0], &buf, 1) > 0) { // un octet est lu dans le tube
  sprintf( Id , "\n\nCLIENT :: octet lu" );
		printf("%d => %c",buf,buf);
    Oc = (byte_t) buf;
    bprintf( Oc , Id , 1 );
  }

  close(pipefd[0]);
  exit(EXIT_SUCCESS);
}
