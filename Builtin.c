#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Builtin.h"

#define DESTINO_HOME  1
#define DESTINO_OUTRO  2


void builtIn_cd(char *novoDiretorio){

    char diretorioAtual[250];
    int mudancaDeDiretorio;
    int tipoDeMudanca = builtIn_cd_avaliarTipoDeMudanca(novoDiretorio);
    
    if(tipoDeMudanca != DESTINO_HOME){
        mudancaDeDiretorio = chdir(novoDiretorio);
        if(mudancaDeDiretorio == 0){ // se o diretorio foi mudado com sucesso
            getcwd(diretorioAtual,250);
            printf("Diretorio atual: %s\n",diretorioAtual);
        }else{
            // TODO Fazer print de erro
        }
    }

    else{
      mudancaDeDiretorio = chdir(getenv("HOME"));
      if(mudancaDeDiretorio == 0){
            getcwd(diretorioAtual,250);
            printf("Diretorio atual: %s\n",diretorioAtual);
      }
    }
}




int builtIn_cd_avaliarTipoDeMudanca(char *destino){
    if(destino == NULL || strcmp(destino,"~") == 0){ // se a pasta destino for vazia ou ~
        return DESTINO_HOME;
    }
    else{
        return DESTINO_OUTRO;
    }
}