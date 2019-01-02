#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#include "client.h"
#include "serveur.h"
#include "string.h"
#include <stdbool.h>


//**********************************************//
//*********************MAIN*********************//
//**********************************************//

int main( int argc, char ** argv ) {
  int pipefd[2];
  int cpid;

  if(argc < 2)  perror("Erreur: Veuillez renseigner un fichier à ouvrir!\n");
  if(pipe(pipefd) == -1)   perror("pipe");
  switch(cpid = fork()){
    case -1 : perror("fork");
    case 0 : client(argv[2], pipefd);
  }
  serveur(argv[1], pipefd );
}
