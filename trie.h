#ifndef __TRIE_H__
#define __TRIE_H__

typedef struct _SList{
	void *data;
	struct _SList* next; 
} SList;

typedef struct _trie{
	unsigned char letra;
	unsigned int code;
	SList *hijos;
	struct _trie *padre;
} Trie;

#define slist_data(l)       (l)->data
#define slist_next(l)       (l)->next

/**
* Agrega un elemento al inicio de la lista, en complejidad O(1).
* Nota: una lista vacia se representa con (SList *) NULL
*/

SList *slist_append(SList *list, void* data);

/** 
 * Crea un nuevo nodo cuya letra es el caracter pasado por argumento y no tiene hijos, en complejidad O(1).
 * Nota: un trie vacio se representa con (Trie *) NULL.
**/

Trie *new_trie(unsigned char c);

/**
 * Inicializa un diccionario con los 256 caracteres de 8 bits.
 */

Trie *initialize();

/**
 * Devuelve el codigo correspondiente a la cadena pasada por argumento en el Trie pasado por argumento.
 * Si la cadena no se encuentra en el trie la agrega y devuelve -1.
 */

unsigned int check_add(Trie *trie, unsigned char *w,int sz);


/**
 * Devuelve el Trie correspondiente a la cadena pasada por argumento en el Trie pasado por argumento.
 * Si la cadena no se encuentra en el trie la agrega.
 */

Trie *add_d(Trie* trie, unsigned char *w, int sz);

/**
 * Destruccion del trie.
 */

void trie_destroy(Trie* node);

/**
 * Devuelve el valor de COD_ACT. 
 */

int cod_act(void);

/**
 * Destruye el trie y crea un nuevo trie
 */

Trie *re_initialize(Trie *t);

#endif /* __TRIE_H__ */
