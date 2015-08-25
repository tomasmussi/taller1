

#ifndef PERSONA_H

#define PERSONA_H


typedef struct persona per_t;


per_t* crear();

void destruir(per_t *persona);

void setEdad(per_t *persona, int edad);

void imprimir(per_t *persona);







#endif
