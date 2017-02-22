#include <stdlib.h>
#include <string.h>
#include "trie.h"

int COD_ACT=0;

SList *slist_append(SList *list, void* data){
  SList *newNode = malloc(sizeof(SList));
  SList *node;
  newNode->data = data;
  newNode->next = NULL;
  if (list == NULL) {
    return newNode;
  }
  node = list;
  while (node->next != NULL) {
    node = node->next;
  }
  node->next = newNode;
  return list;
}

SList *slist_prepend(SList *list, void* data){
  SList *newNode = malloc(sizeof(SList));
  newNode->data = data;
  newNode->next = list;
  return newNode;
}

Trie *new_trie(unsigned char c){
	Trie *new=malloc(sizeof(Trie));
	new->code=COD_ACT;
	COD_ACT++;
	new->hijos=NULL;
	new->padre=NULL;
	new->letra=c;
	return new;
}

Trie *initialize(){
	Trie *dic=malloc(sizeof(Trie));
	SList *hijos=NULL;
	dic->code=-3; //se le asigna el código -3 al Trie raíz para identificarlo.
	dic->padre=NULL;
	dic->letra=0;
	COD_ACT=0;

	int i;
	for(i=0; i<256; i++){
		Trie *new=new_trie(i);
		new->padre=dic;
		hijos=slist_append(hijos,new);
	}

	dic->hijos=hijos;

	return dic;
}

unsigned int check_add(Trie *trie, unsigned char *w,int sz){ //tiene que poder manejar cadenas que incluyan 8 bits en 0 (el caracter '\0')
	Trie *padre=trie,*dic=trie;
	SList *list=trie->hijos;

	while(sz != 0){
		if(list==NULL){ //no está
			Trie *new=new_trie(*w);
			new->padre=padre;
			padre->hijos=slist_prepend(padre->hijos,new);
			return (unsigned int)-1;
		}
		dic=(Trie*)(list->data);
		if(dic->letra==*w){
			padre=dic;
			list=dic->hijos;
			w=&w[1];
			sz--;
		}
		else{
			list=list->next;
		}
	}

	return padre->code;
}

Trie *add_d(Trie *trie, unsigned char *w,int sz){ //tiene que poder manejar cadenas que incluyan 8 bits en 0 (el caracter '\0')
	Trie *padre=trie,*dic=trie;
	SList *list=trie->hijos;

	while(sz != 0){
		if(list==NULL){ //no está
			Trie *new=new_trie(*w);
			new->padre=padre;
			padre->hijos=slist_prepend(padre->hijos,new);
			return new;
		}
		dic=(Trie*)(list->data);
		if(dic->letra==*w){
			padre=dic;
			list=dic->hijos;
			w=&w[1];
			sz--;
		}
		else{
			list=list->next;
		}
	}

	return padre;
}

void trie_destroy(Trie* node){
	if (NULL == node)
 	   return;

 	SList *listToDelete;	
	SList *p = node->hijos;
	
	while (p) {
	    trie_destroy(p->data);
		listToDelete=p;    
		p = p->next;
	  	free(listToDelete);
	}
	
	free(node);

	return;
}

Trie *re_initialize(Trie *t){
	trie_destroy(t);
	t=(Trie *)initialize();
	return t;
}

int cod_act(){
	return COD_ACT;
}
