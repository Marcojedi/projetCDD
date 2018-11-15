#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "global.h"
#include "tools.h"


void bprintf( const byte_t Oc, const char * identifer, const int mode ) {
  static char buffer[9];
  int n;

  printf( "%s = 0b" , identifer );
  for( n = 0 ; n < 8 ; n++ ) {
    byte_t bit = (1 << n);

    buffer[7-n] = ((Oc & bit) ? '1' : '0');
  }
  buffer[8] = '\0';
  printf( "%s" , buffer );
  if( mode == 1 ) printf( " = %u" , Oc );
	printf( "\n" );
}

byte_t bread( ) {
  int c;

  printf( "un octet : " );
  scanf( " %d" , &c );

  assert( -1 < c && c < 256 );

  return (byte_t) c;
}

int bit_read( byte_t Oc , int n ) {
  assert( -1 < n && n < 8 );

  byte_t Dn = U << n;

  return ((Oc & Dn) ? 1 : 0);
}

byte_t bit_write( byte_t Oc , int n ) {
  assert( -1 < n && n < 8 );

  byte_t Dn = U << n;

  return (Oc ^ Dn);
}
