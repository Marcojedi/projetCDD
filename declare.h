#ifndef _DECLARE_
#define _DECLARE_
#include <stdbool.h>

#define KEY 25

typedef struct{
    int index;
    char * chaine;
    bool estDispo;
} mot_t;

typedef struct{
    mot_t tabMots[BUFSIZ];
    int size;
    int lastIndex;
} dico_t;

typedef struct{
    int size;
    int tableauValeurs[BUFSIZ];
} valeurs_t;

extern dico_t ajoutMot(dico_t * dico, mot_t *mot);
extern dico_t creerDico();
extern valeurs_t creerTableau();

#endif
