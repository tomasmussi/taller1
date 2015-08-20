#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
  char nombre[20];
  char *buffer;
  FILE *fp;
  
  strcpy( nombre, argv[1] );
  fp = fopen( nombre, "r" );
  if( fp == NULL ) return 2;

  buffer = malloc( sizeof(int) ); /* buffer innecesario */
  
  while( !feof(fp) )
  {
    int c = fgetc(fp);
    if( c != EOF )
      printf( "%c", (char) c );
  }

  return 0;
}

