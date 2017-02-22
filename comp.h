#ifndef __COMP_H__
#define __COMP_H__

/**
 * Calcula el piso del logaritmo en base dos de x. Si x es 0 devuelve -1.
**/

int log_2(unsigned int x);

/**
 *Escribe en el archivo pasado por argumento un numero de 8 bits segun el entero pasado
 */

FILE* escribir(unsigned int a, FILE *f);

/**
 * Comprime un archivo y lo escribe en out
**/

FILE* comprimir(char *archivo, char *out);

#endif /* __COMP_H__ */
