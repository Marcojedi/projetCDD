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

dico_t ajoutMots(dico_t * dico, mot_t *mot){
    dico->lastIndex = ++dico->lastIndex;
    mot->index = dico->lastIndex;
    dico->tabMots[dico->size] = *mot;
    dico->size++;
    return *dico;
}

/* fonction qui decrypte le message */
int decrypterXOR(int code){
    code = code ^ KEY;
    return code;
}

/* fonction qui concatène une string et un char */
char * strconcats(char * chaine,char c){
    int len = strlen(chaine);
    char *retour=NULL;
    retour=malloc((len+1)*sizeof(char));
    strcpy(retour,chaine);
    retour[len] = c;
    retour[len+1] = '\0';
    return retour;
}

/* fonction qui verifie si la chaine trouvée est presente dans le dictionnaire */
bool chercherDansDicos(dico_t *dico,char * chaine){
    if(strlen(chaine)==1)
        return true;
    for(int i=0; i<dico->size;i++){
        if(strcmp(dico->tabMots[i].chaine,chaine)==0){
            return true;
        }
    }
    return false;
}

/* fonction qui verifie si la chaine trouvée est presente dans le dictionnaire */
char * chercherDansDicoByIndex(dico_t *dico, int code){
    for(int i=0; i<dico->size;i++){
        if(dico->tabMots[i].index == code){
            return dico->tabMots[i].chaine;
        }
    }
}

char * toChar(int entier) {
	return entier;
}

/* execution du client */
void client(char * dest, int pipefd[2]) {	
    int c,i;
    char *S = "";
    char m;
    char *valeurCode = "";
    dico_t dico;
    valeurs_t tableau = creerTableau();
      
    close(pipefd[1]);          // Close unused write end
    printf("CLIENT\n------\n");
    while (read(pipefd[0], &c, sizeof(c)) > 0) { // un octet est lu dans le tube  
        c = decrypterXOR(c);

        if (c <= 255) {
        	m = toChar(c);
        	printf("%c\n", m);
        	if (strlen(strconcats(S,m)) == 1)	{
        		S = strconcats(S,m); 
        	} else {
        		if (chercherDansDicos(&dico,strconcats(S,m))) {
        			S = strconcats(S,m);
        		} else {
        			mot_t motToAdd;
		            motToAdd.chaine = strconcats(S,m);
		            ajoutMots(&dico,&motToAdd);
		            S = strconcats("",m);
        		}    		
        	}
        } else {
        	strcpy(valeurCode, chercherDansDicoByIndex(&dico,c));
        	printf("%s\n", valeurCode);
        }
    }

    exit(EXIT_SUCCESS);
}
