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
  int buf;
  char * Id = (char *) calloc( 10, sizeof(char) );
  
  close(pipefd[1]);          // Close unused write end
  printf("CLIENT\n------\n");
  while (read(pipefd[0], &buf, sizeof(buf)) > 0) { // un octet est lu dans le tube
		printf("%d\n",buf);
  }

  exit(EXIT_SUCCESS);

/*
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
*/
}
