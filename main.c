#include <stdio.h>
#include "descomp.h"
#include "comp.h"

int main(void){
    puts("Compressing...");
    comprimir("input","input_comp");
    
    puts("Done! Press Enter to decompress");
    getchar();
    puts("Decompressing...");
    descomprimir("input_comp","output");
    
    puts("Done!");
    return 0;
}
