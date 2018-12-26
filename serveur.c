#include "sys/types.h"
#include "sys/wait.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

#include "global.h"
#include "tools.h"
#include "LZW.h"
#include <stdbool.h>



/*void serveur(char *src,int pipefd[2] ) {
  char * mots[3840];
  int i=0,nb_mot;
  char buf[BUFSIZ]; char m;

  close( pipefd[0] );		// Close unused read end
  FILE * fd;
  fd = fopen(src,"r");
	if(fd==NULL) perror("Erreur ouverture, fichier introuvable"); 
  while(fgets(buf,BUFSIZ,fd)!=NULL){
		while(buf[i]!='\n'){ //Recupère chaque lettre
				m = buf[i];
				write( pipefd[1], &m , 1 );
				i++;
		}
	i=0;
  }

  printf("le serveur ferme\n\n");
  close(pipefd[1]); // Reader will see EOF
  wait(NULL); // Wait for child
  exit(EXIT_SUCCESS);
}*/





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

void emettreCode(dico_t *dico,char * S,int pipefd[2]){
  int code;
    if(strlen(S)==1){
        code = S[0];
        //printf("code emit = %d ",code);
        write( pipefd[1], &code, sizeof(code) );
    }
    else{
        for(int i=0; i<dico->size;i++){
            //printf("compare '%s' avec '%s'\n",dico->tabMots[i].chaine,chaine);
            if(strcmp(dico->tabMots[i].chaine,S)==0){
                //printf("code emit = %d ",dico->tabMots[i].index);
                code = dico->tabMots[i].index;
                write( pipefd[1], &code, sizeof(code));
            }
        }
    }
}

//*********************MAIN*********************//

int serveur(char *src,int pipefd[2]){  
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
        //printf(" m='%c' ", m);
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
        //printf(" S='%s' \n",S); 
    }
    emettreCode(&dico,S,pipefd);
    printf("le serveur ferme\n\n");

    close(pipefd[1]); // Reader will see EOF
    wait(NULL); // Wait for child
    exit(EXIT_SUCCESS);
}