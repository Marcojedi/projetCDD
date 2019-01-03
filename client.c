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

void visionDico(dico_t *dico){
    printf("\n");
    for(int i =0;i<dico->size;i++){    
        printf("Index : %d || Chaine : '%s'\n",dico->tabMots[i].index,dico->tabMots[i].chaine);
    }
}

/* fonction qui verifie si la chaine trouvée est presente dans le dictionnaire */
char * chercherDansDicoByIndex(dico_t *dico, int code){
    for(int i=0; i<dico->size;i++) {
        if(dico->tabMots[i].index == code){
            return strdup(dico->tabMots[i].chaine);
        }
    }
    visionDico(dico);
    return "\nErreur : Valeur non trouvée\n";
}

char * toChar(int entier) {
	return entier;
}

/* execution du client */
void client(char * dest, int pipefd[2]) {	
    sleep(1);
    int c,i;
    char *S = "";
    char m;
    char *M = "";
    
    FILE *fw = fopen("decoding.txt","w");
    dico_t dico = creerDico();
    valeurs_t tableau = creerTableau();
      
    close(pipefd[1]);          // Close unused write end
    printf("CLIENT\n------\n");
    while (read(pipefd[0], &c, sizeof(c)) > 0) { // un octet est lu dans le tube    
        if (c <= 255) {
        	m = toChar(c);
        	printf("%c", m);
            fprintf(fw, "--> %c a ete decode \n",c);
        	if (strlen(strconcats(S,m)) == 1)	{
        		S = strconcats(S,m); 
        	} else {
        		if (chercherDansDicos(&dico,strconcats(S,m))==true) {
        			S = strconcats(S,m);
        		} else {
        			mot_t motToAdd;
		            motToAdd.chaine = strconcats(S,m);
		            ajoutMots(&dico,&motToAdd);
                    fprintf(fw, "--> %s ajouter au dico \n",strconcats(S,m));
		            S = strconcats("",m);
        		}    		
        	}
        } else {
            char * back = malloc(BUFSIZ*sizeof(char));
        	M = chercherDansDicoByIndex(&dico,c);
        	for (int j = 0; j < strlen(M); j++) {
                printf("%c",M[j]);
                fprintf(fw, "'%c' a ete decode! \n",M[j]);
                strcpy(back,S);
                S = strconcats(S,M[j]);
        		if (chercherDansDicos(&dico,S)) {
                    printf(""); 
	        	} else {
                    strcpy(S,back);
	        		mot_t motToAdd;
			        motToAdd.chaine = strconcats(S,M[j]);
			        ajoutMots(&dico,&motToAdd);
                    fprintf(fw, "'%s' ajouter au dico \n",strconcats(S,M[j]));
                    S = strconcats("",M[j]);
	        	}
        	}  	
        }
    }
    fclose(fw);
    printf("\n");
    exit(EXIT_SUCCESS);
}
