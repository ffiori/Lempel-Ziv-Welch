#include <stdio.h>
#include "trie.h"
#include "comp.h"
#include "common.h"

int sobra_bits=0;//cantidad de bits que lei del archivo pero no todavia no escribi en el archivo comprimido
unsigned int sobra_num=0;//numero que falta escribir en el archivo comprimido

//double log2(double x){return log(x)/log(2);}

int log_2(unsigned int x){
    int rta=-1;
    while(x>0){
        rta++;
        x >>= 1;
    }
    return rta;
}

FILE* escribir(unsigned int a, FILE *f){
	//int bits_act = floor(log2(cod_act()-2))+1;//cantidad de bits que ocupa cada codigo
	int bits_act = log_2(cod_act()-2)+1;//cantidad de bits que ocupa cada codigo

	sobra_bits = sobra_bits + bits_act - 8;
	unsigned int b;

	if(bits_act==8){
		fputc(a, f);
	}
	else{
		b = a >> sobra_bits;
		sobra_num = b | sobra_num;//agrego a sobra_num los primeros 8-sobra_bits bits de a
		fputc(sobra_num, f);
		a = a-(b << sobra_bits);
			if(sobra_bits>=8){//se puede seguir escribiendo en el archivo
				sobra_bits=sobra_bits-8;
				b = a >> sobra_bits;
				fputc(b, f);
				a = a-(b << sobra_bits);
			}
		sobra_num = a;
		sobra_num = sobra_num << (8-sobra_bits);//completa a 8 bits agregando 0 a la derecha
	}

	return f;
}

FILE* comprimir(char *archivo, char *out){
	int i,j;
	unsigned char w[MAX_STRLEN+1]={0};

	FILE *f;
	f=fopen(archivo, "rb");

	if(f == NULL){
		return f;
	}

	FILE *new=fopen(out, "wb");
	Trie *dic=initialize();
	unsigned int prev, act;//codigo de la penultima y ultima cadena leida respectivamente
	int last=-1;//posicion del ultimo caracter en w

	while(!feof(f)){
		last++;
		w[last]=fgetc(f);
       		act = check_add(dic,w,last+1);
	
		if(cod_act() > MAX_STRLEN){//ya use todos los codigos que ocupan a lo sumo 16 bits
			new=escribir(prev,new);
			dic=re_initialize(dic);
			w[0]=w[last];
			for(; last>0; last--)
				w[last]=0;
			prev=check_add(dic,w,last+1);
			continue;
		}

		if(act!=(unsigned int)-1){//la cadena ya estaba en dic
				prev = act;
		}else{
			new=escribir(prev, new);
			w[0]=w[last];
			for(; last>0; last--)
				w[last]=0;
			prev=*w;

		}//end if
	}//end while

    if(sobra_bits){
		fputc(sobra_num, new);
	}

	trie_destroy(dic);

	fclose(f);

	fclose(new);

	return new;
}
