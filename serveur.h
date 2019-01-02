#ifndef _serveur_h_
#define _serveur_h_

#include <stdbool.h>
#include "declare.h"

dico_t creerDico();
dico_t ajoutMot(dico_t * dico, mot_t *mot);
char * strconcat(char * chaine,char c);
bool chercherDansDico(dico_t *dico,char * chaine);
int crypterXOR(int code);
void emettreCode(dico_t *dico,char * S,int pipefd[2]);
void serveur(char *src, int pipefd[2]);

#endif // _serveur_h_
