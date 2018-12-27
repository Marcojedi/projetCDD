#include "stdlib.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "client.h"

valeurs_t creerTableau(){
    valeurs_t tableau;
    tableau.size = 0; 
    return tableau;
}

/* fonction qui decrypte le message */
int decrypterXOR(int code){
    code = code ^ KEY;
    return code;
}

/* execution du client */
void client(char * dest, int pipefd[2]) {	
    int buf,i;
    int key = 25;
    valeurs_t tableau = creerTableau();
      
    close(pipefd[1]);          // Close unused write end
    printf("CLIENT\n------\n");
    while (read(pipefd[0], &buf, sizeof(buf)) > 0) { // un octet est lu dans le tube        
        buf = decrypterXOR(buf);

        tableau.tableauValeurs[tableau.size] = buf;
        tableau.size = ++tableau.size;
    }

    //affichage du tableau contenant les entiers
    for (i = 0; i < tableau.size; i++) {
        printf("%i\n", tableau.tableauValeurs[i]);
    }

    exit(EXIT_SUCCESS);
}
