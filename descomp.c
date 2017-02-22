#include <stdio.h>
#include <string.h>
#include "trie.h"
#include "descomp.h"
#include "common.h"

int SZP=1,SZ=1;//longitud de wprev y w respectivemente
int sobran_bits = 0;//cantidad de bits que fueron leidos pero no escritos
unsigned int sobran_num = 0;//numero que todavia no fue escrito
int bits_act = 9;//cantidad de bits que ocupa los codigos en el archivo comprimido
int contador = 0;//cantidad de numeros leidos con la misma cantidad de bits

void translate(Trie *arr[MAX_STRLEN], unsigned int codigo, unsigned char *w){
	unsigned char wtemp[MAX_STRLEN]={0};
	int i,j;

	Trie *act=arr[codigo];

	for(i=0; act->padre!=NULL; i++,act=act->padre)
		wtemp[i]=act->letra;
    //en wtemp esta la cadena correspondiente al codigo pero en orden inverso
	i--;

	for(j=0; i>=0; j++,i--)
		w[j]=wtemp[i];
    //guardo en w la cadena correspondiente al codigo en el orden correcto
	SZ=j;

	return;
}

unsigned int transf(unsigned int a){
	unsigned int res;

	sobran_num = sobran_num << 8;
	sobran_num = sobran_num | a;//agrego el nuevo numero a sobran_num

	sobran_bits += 8;

	if(sobran_bits<bits_act)
		res=(unsigned int)-1;//la cantidad de bits no es suficiente para emitir un codigo
	else{
		sobran_bits = sobran_bits - bits_act;

		res = sobran_num >> sobran_bits ;
		sobran_num = sobran_num - (res << sobran_bits); //saco a sobran_num lo que ya use en res
	}

	contador++;
	if(contador == (1<<(bits_act-4))*bits_act){//ya obtuve todos los codigos de bits_act bits.
		contador = 0;
		bits_act++;
	}

	return res;
}

FILE *descomprimir(const char* file, char *out){
	FILE * f=fopen(file, "rb");
	FILE * desc= fopen(out,"w") ;

	if(!f)
		return f;

	Trie *dic=initialize();
	SList *primeros=dic->hijos;
	unsigned char c;
	unsigned char w[MAX_STRLEN]={0},wprev[MAX_STRLEN]={0};
	unsigned int act,i;
	Trie *codigos[MAX_STRLEN]={NULL}; //en este arreglo guardo punteros al Trie correspondiente a cada código.

	for(i=0; i<256; i++,primeros=primeros->next)
		codigos[i]=(Trie *)(primeros->data);

	//escribo la primera letra correspondiente al primer código leído que es de 8 bits.
	c=fgetc(f);
	wprev[0]=c;
	fputc(c, desc);

	while(1){
		if(bits_act > MAX_CODELEN){//ya use todos los codigos que ocupan a lo sumo MAX_CODELEN bits, entonces reinicio el diccionario.
			c=fgetc(f);

			if(feof(f)){
				break;
			}

			dic=re_initialize(dic);
			bits_act=9;
			wprev[0]=c;
			fputc(c, desc);
			SZ=1;
			SZP=1;
			primeros=dic->hijos;
			for(i=0; i<256; i++,primeros=primeros->next)
				codigos[i]=(Trie *)(primeros->data);
			continue;
		}

		c=fgetc(f);

		if(feof(f)){//ya lei EOF
			break;
		}

		act = transf(c);

		if(act == (unsigned int)-1){
			c=fgetc(f);
			if(!feof(f)) //si llegué al EOF entonces hubo algo mal en la compresión, porque nunca le deben faltar bits.
				act = transf(c);
		}

		if(cod_act() == act){ //caso cScSc (si cod_act()==act entonces todavía no fue agregado al dic)
			wprev[SZP]=wprev[0];
			SZP++;

			fwrite(wprev, sizeof(char), SZP, desc);

			codigos[i]=add_d(dic, wprev,SZP);
			i++;
		}
		else{
			SZ=0;
			translate(codigos,act,w);

			fwrite(w, sizeof(char), SZ, desc);
			wprev[SZP]=w[0];
			SZP++;

			codigos[i]=add_d(dic, wprev,SZP);
			i++;

			memcpy(wprev,w,SZ); //en wprev guardo la última cadena que se escribió al archivo.

			SZP=SZ;
		}
	}

	return desc;
}
