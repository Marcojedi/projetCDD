#include "stdlib.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "client.h"

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
    return strdup(retour);
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
    
    return "ERROR : INDEX DOESN'T EXIST\n";
}

char * toChar(int entier) {
	return entier;
}

/* execution du client */
void client(char * dest, int pipefd[2]) {	
     close(pipefd[1]);  
    int c,i;
    char *S = "";
    char m;
    char *M = "";
    
    FILE *fw = fopen("decoding.txt","w");
    dico_t dico = creerDico();
      
           // Close unused write end
    printf("CLIENT\n------\n");
    while (read(pipefd[0], &c, sizeof(c)) > 0) { // un octet est lu dans le tube    
        if(dico.size<BUFSIZ-2){
            if (c <= 255) {
                m = toChar(c);
                fprintf(fw,"%c", m);
                if (strlen(strconcats(S,m)) == 1)	{
                    S = strconcats(S,m); 
                } else { // OK
                    if (chercherDansDicos(&dico,strconcats(S,m))==true) {
                        S = strconcats(S,m);
                    } else { //OK
                        mot_t motToAdd;
                        motToAdd.chaine = strconcats(S,m);
                        ajoutMots(&dico,&motToAdd); //--->PROBLEME
                        S = strconcats("",m);
                    }   	
                }
            } else {
                char * back = malloc(BUFSIZ*sizeof(char));
                M = chercherDansDicoByIndex(&dico,c);
                for (int j = 0; j < strlen(M); j++) {
                    fprintf(fw,"%c",M[j]);
                    strcpy(back,S);
                    S = strconcats(S,M[j]);
                    if (chercherDansDicos(&dico,S)) {
                        printf(""); 
                    } else {
                        strcpy(S,back);
                        mot_t motToAdd;
                        motToAdd.chaine = strconcats(S,M[j]);
                        ajoutMots(&dico,&motToAdd);
                        S = strconcats("",M[j]);
                    }
                }  	
                free(back);
            }
        }
        else{
            m = toChar(c);
            fprintf(fw,"%c", m);
        }
    }
    fclose(fw);
    close(pipefd[0]);
    printf("Decodeur execute avec succès voir le fichier decoding.txt generer pour le detail\n");
    printf("\n");
    exit(EXIT_SUCCESS);
}
