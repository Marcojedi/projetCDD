#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct{
    int index;
    char * chaine;
} mot_t;

typedef struct{
    mot_t tabMots[BUFSIZ];
    int size;
    int lastIndex;
} dico_t;

dico_t ajoutMot(dico_t * dico, mot_t *mot){
    dico->size++;
    dico->lastIndex = ++dico->lastIndex;
    mot->index = dico->lastIndex;
    dico->tabMots[dico->size] = *mot;
    return *dico;
}

dico_t creerDico(mot_t *mot){
    dico_t dico;
    dico.size=0;
    dico.lastIndex = 256;
    mot->index = dico.lastIndex;
    dico.tabMots[0] = *mot;
    
    return dico;
}

//MAIIIIIIIIIIIIIIIIIIIIIIINNNNNNNNNNNNNNNNNN

int main(int argc,char * argv[]){
    char S[BUFSIZ];

    mot_t mot;
    mot.chaine = "ok1";

    mot_t mot2;
    mot2.chaine = "testi";


    dico_t dico = creerDico(&mot);
    dico = ajoutMot(&dico,&mot2); 
    dico = ajoutMot(&dico,&mot);

    printf("%d , chaine = %s \n",dico.tabMots[0].index,dico.tabMots[0].chaine);
    printf("%d , chaine = %s \n",dico.tabMots[1].index,dico.tabMots[1].chaine);
    printf("%d , chaine = %s \n",dico.tabMots[2].index,dico.tabMots[2].chaine);
 /* 
    char c;
    FILE * fd;
    fd = fopen(argv[1],"r");
        if(fd==NULL) perror("Erreur ouverture, fichier introuvable");
    while ((c = fgetc(fd)) != EOF){
        printf("%c",c);
    }
*/
    return 0;
}