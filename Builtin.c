#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Builtin.h"


void builtIn_cd(char *novoDiretorio){
    int mudancaDeDiretorio;

    if( novoDiretorio == NULL || strcmp(novoDiretorio,"~") == 0){ 
        // Se a entrada para o diretorio destino for vazia ou "~", o diretorio destino será HOME
        mudancaDeDiretorio = chdir(getenv("HOME"));
        if(mudancaDeDiretorio != 0){ // Se a mudanda de diretório falhou
            fprintf(stderr,"Diretório destino inexistente.\n");
        }
    }
    else{ // Se o diretorio destino não for HOME
        mudancaDeDiretorio = chdir(novoDiretorio);
        if(mudancaDeDiretorio != 0){ // Se a mudanda de diretório falhou
            fprintf(stderr,"Diretório destino inexistente.\n");
        }
    }
}







