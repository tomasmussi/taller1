#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LARGO_FILE 20
#define POS_NOMBRE_ARCHIVO 1
#define ARCHIVO_NO_ENCONTRADO 1
#define SALIDA_NORMAL 0

int main(int argc, char *argv[])
{
  char nombre[LARGO_FILE];
  char *buffer;
  FILE *fp;
  
  strcpy(nombre, argv[POS_NOMBRE_ARCHIVO]);
  fp = fopen(nombre, "r");
  if ( fp == NULL ) return ARCHIVO_NO_ENCONTRADO;

  buffer = malloc(sizeof(int)); /* buffer innecesario */
  
  while ( !feof(fp) )
  {
    int c = fgetc(fp);
    if ( c != EOF )
      printf("%c", (char) c);
  }

  fclose(fp);
  free(buffer);

  return SALIDA_NORMAL;
}

