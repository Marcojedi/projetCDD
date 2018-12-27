#ifndef _client_h_
#define _client_h_

#include "declare.h"

valeurs_t creerTableau();
int decrypterXOR(int code);
void client(char * dest, int pipefd[2]);

#endif // _client_h_
