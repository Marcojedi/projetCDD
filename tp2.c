#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#include "global.h"
#include "client.h"
#include "serveur.h"


/**
 * @brief byte constants
 */
const byte_t Z = 0b00000000;
const byte_t U = 0b00000001;

int main( int argc, char ** argv ) {
  int pipefd[2];

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  int cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  
  if (cpid == 0) {    /**< Child reads from pipe */
    client( pipefd );
  }
  else {           /**< Parent writes to pipe */
    serveur( pipefd );
  }
}
