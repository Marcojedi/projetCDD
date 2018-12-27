#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "declare.h"
#include "serveur.h"

dico_t ajoutMot(dico_t * dico, mot_t *mot){
    dico->lastIndex = ++dico->lastIndex;
    mot->index = dico->lastIndex;
    dico->tabMots[dico->size] = *mot;
    dico->size++;
    return *dico;
}

dico_t creerDico(){
    dico_t dico;
    dico.size=0;
    dico.lastIndex = 255;
    return dico;
}

/* fonction qui concatène une string et un char */
char * strconcat(char * chaine,char c){
    int len = strlen(chaine);
    char *retour=NULL;
    retour=malloc((len+1)*sizeof(char));
    strcpy(retour,chaine);
    retour[len] = c;
    retour[len+1] = '\0';
    return retour;
}

/* fonction qui verifie si la chaine trouvée est presente dans le dictionnaire */
bool chercherDansDico(dico_t *dico,char * chaine){
    if(strlen(chaine)==1)
        return true;
    for(int i=0; i<dico->size;i++){
        if(strcmp(dico->tabMots[i].chaine,chaine)==0){
            return true;
        }
    }
    return false;
}

/* fonction qui crypte le message */
int crypterXOR(int code){
    code = code ^ KEY;
    return code;
}

/* fonction qui envoi au client les valeurs emises par LZW */
void emettreCode(dico_t *dico,char * S,int pipefd[2]){
  int code;
    if(strlen(S)==1){
        code = S[0];
        code = crypterXOR(code);
        write( pipefd[1], &code, sizeof(code) );
    }
    else{
        for(int i=0; i<dico->size;i++){
            if(strcmp(dico->tabMots[i].chaine,S)==0){
                code = dico->tabMots[i].index;
                code = crypterXOR(code);
                write( pipefd[1], &code, sizeof(code));
            }
        }
    }
}

/* execution du serveur */
void serveur(char *src,int pipefd[2]){  
    close(pipefd[0]);

    //declaration variable
    dico_t dico = creerDico();
    write(pipefd[1],110,1);
    char m;
    char * S = "";
    FILE * fd;

    //debut algorithme
    fd = fopen(src,"r"); if(fd==NULL) perror("Erreur ouverture, fichier introuvable");
    printf("SERVEUR\n-------\n");
    while ((m = fgetc(fd)) != EOF){
        if(chercherDansDico(&dico,strconcat(S,m))==true){
            S = strconcat(S,m);           
        }
        else{
            emettreCode(&dico,S,pipefd);
            mot_t motToAdd;
            motToAdd.chaine = strconcat(S,m);
            ajoutMot(&dico,&motToAdd);
            S = strconcat("",m);
        }
    }
    emettreCode(&dico,S,pipefd);
    printf("le serveur ferme\n\n");

    close(pipefd[1]);
    wait(NULL);
    exit(EXIT_SUCCESS);
}