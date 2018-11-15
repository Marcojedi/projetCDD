#ifndef _TOOLS_
#define _TOOLS_

#include "global.h"
/** 
 * signature des fonctions bit à bit
 */

void bprintf( const byte_t Oc, const char *ident, const int mode );
// afficher un octet au format binaire et si mode == 1 en entier

byte_t bread();
// lire un octet en s'assurant que les valeurs sont entre 0 et 255

int bit_read ( byte_t Oc , int n );
// extraire le nième bit de l'octet avec n compris entre 0 et 7

byte_t bit_write( byte_t Oc , int n );
// modifier le nième bit de l'octet avec n compris entre 0 et 7

#endif
