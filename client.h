#ifndef _client_h_
#define _client_h_

#include <stdbool.h>
#include "declare.h"

char * strconcats(char * chaine,char c);
bool chercherDansDicos(dico_t *dico,char * chaine);
char * chercherDansDicoByIndex(dico_t *dico, int c);
int decrypterXOR(int code);
void client(char * dest, int pipefd[2]);

#endif // _client_h_
