#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <stdbool.h>

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

char * strconcat(char * chaine,char c){
    int len = strlen(chaine);
    char *retour=NULL;
    retour=malloc((len+1)*sizeof(char));
    strcpy(retour,chaine);
    retour[len] = c;
    retour[len+1] = '\0';
    return retour;
}

bool chercherDansDico(dico_t *dico,char * chaine){
    if(strlen(chaine)==1)
        return true;
    //printf("%s\n-----\n",chaine);
    for(int i=0; i<dico->size;i++){
        //printf("compare '%s' avec '%s'\n",dico->tabMots[i].chaine,chaine);
        if(strcmp(dico->tabMots[i].chaine,chaine)==0){
            return true;
        }
    }
    return false;
}

void emettreCode(dico_t *dico,char * S){
    if(strlen(S)==1){
        int code = S[0];
        printf("code emit = %d ",code);
    }
    else{
        for(int i=0; i<dico->size;i++){
            //printf("compare '%s' avec '%s'\n",dico->tabMots[i].chaine,chaine);
            if(strcmp(dico->tabMots[i].chaine,S)==0){
                printf("code emit = %d ",dico->tabMots[i].index);
            }
        }
    }
}

//*********************MAIN*********************//

int main(int argc,char * argv[]){   
    //declaration variable
    dico_t dico = creerDico();
    char m;
    char * S = "";
    FILE * fd;

    //debut algorithme
    fd = fopen(argv[1],"r"); if(fd==NULL) perror("Erreur ouverture, fichier introuvable");
    while ((m = fgetc(fd)) != EOF){
        printf(" m='%c' ", m);
        if(chercherDansDico(&dico,strconcat(S,m))==true){
            S = strconcat(S,m);
            
        }
        else{
            emettreCode(&dico,S);
            mot_t motToAdd;
            motToAdd.chaine = strconcat(S,m);
            ajoutMot(&dico,&motToAdd);
            S = strconcat("",m);
        }
        printf(" S='%s' \n",S); 
    }
    emettreCode(&dico,S);
    return 0;
}