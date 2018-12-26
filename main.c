#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#include "global.h"
#include "client.h"
#include "serveur.h"
#include "LZW.h"
#include "string.h"
#include <stdbool.h>



/**
 * @brief byte constants
 */

typedef struct {
	char * mots[3840];
	int nb_mots;
} dico_t;

static dico_t DICO;

const byte_t Z = 0b00000000;
const byte_t U = 0b00000001;


int main( int argc, char ** argv ) {
  int pipefd[2];

  if(argc < 2){
    perror("Erreur: Veuillez renseigner un fichier à ouvrir!\n");
    exit(EXIT_FAILURE);
  } 
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
    client(argv[2], pipefd );
  }
  else {         /**< Parent writes to pipe */
    serveur(argv[1], pipefd );
  }
}
