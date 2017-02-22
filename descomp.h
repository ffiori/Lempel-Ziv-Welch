#ifndef __DESCOMP_H__
#define __DESCOMP_H__
#include "trie.h"
#include "common.h"

/**
 * Guarda en w la cadena corresondiente al codigo pasado por argumento
 **/

void translate(Trie* arr[MAX_STRLEN], unsigned int codigo, unsigned char* w);

/**
 * Devuelve un entero (código que se debe tomar como el siguiente) con la cantidad de bits correspondiente, segun el numero pasado por argumento (que son los 8 bits que se leyeron del archivo)
**/

unsigned int transf(unsigned int a);

/**
 * Descomprime un archivo y lo escribe en out
**/

FILE *descomprimir(const char* file, char *out);

#endif /* __DESCOMP_H__ */
