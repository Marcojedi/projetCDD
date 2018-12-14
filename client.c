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
#include "LZW.h"

 
void client(char * dest, int pipefd[2] ) {	
  /*byte_t Oc;
  int buf;
  char * Id = (char *) calloc( 10, sizeof(char) );
	
  close(pipefd[1]);          // Close unused write end
  while (read(pipefd[0], &buf, 1) > 0) { // un octet est lu dans le tube
		printf("%c",buf);
    Oc = (byte_t) buf;
    bprintf( Oc , Id , 1 );
  }

  close(pipefd[0]);
  exit(EXIT_SUCCESS);*/

  byte_t Oc;
  byte * enc;
  char * Id = (char *) calloc( 10, sizeof(char) );
  
  close(pipefd[1]);

  read(pipefd[0], &enc, 1);
  //---------------------------
  byte *dec = lzw_decode(enc);
  printf("decoded size: %d\n", _len(dec));
 
  _del(dec);
  //---------------------------

  close(pipefd[0]);
  exit(EXIT_SUCCESS);
}
