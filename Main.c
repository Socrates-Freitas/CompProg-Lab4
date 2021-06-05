#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <setjmp.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "Parser.h"

#define MAX_INPUT_SIZE 150


void printShell();
void commandRunner();
int handleBuiltIn(char *comando);


int main(int argc, char **argv){
    while(1){
        commandRunner();
    }
    return 0;
}



void printShell(){
    printf("shell> ");
}

/*
* Aqui os comandos serão rodados
* TODO: Colocar checagem para built in
*/
void commandRunner(){
    char entrada[MAX_INPUT_SIZE];
    char **argv;
    int builtInType, isBackground;
    int numeroDeElementos, pid;

    char *binFolder = "/bin/";
    char comandoConcatenado[MAX_INPUT_SIZE];

    printShell();
    fgets(entrada,MAX_INPUT_SIZE,stdin);
    removerNewLineDaString(entrada); // retira o \n no final da string de entrada
    if(feof(stdin)){
        exit(1);
    }

   // int pid = fork(); // cria novo processo
    argv = criarArgv(entrada,&numeroDeElementos);
    if(argv){
        builtInType = handleBuiltIn(argv[0]);
        if(builtInType == -1){
            pid = fork();
            if(pid == 0){
                // Aqui subtrai por 2 porque o último(numeroDeElementos) elemento é NULL
                isBackground = isBackgroundProcess(argv[numeroDeElementos - 2]); 

                // for(int i =0; *(argv + i);i++){
                //     printf("-> %s\n",argv[i]);
                // }
                if(isBackground != 0){
                   // printf("é sim\n");
                }
                else{
                    //printf("num e nao\n");
                }

                criarTextoDoComando(comandoConcatenado,binFolder,argv[0]);

                execve(comandoConcatenado,argv,__environ);
                exit(0);
            }
            else{
                waitpid(-1,NULL,0);
            }
        }

        free(argv); // liberando recursos alocados

    }else{
        printf("deu ruim\n");
    }


    return;

}

int handleBuiltIn(char *comando){
    if(strcmp(comando,"fg") == 0){
        printf("fg...\n");
        return 0;
    }
    else if(strcmp(comando,"bg") == 0 ){
        printf("bg...\n");
        return 0;
    }
    else if(strcmp(comando,"jobs") == 0 ){
        printf("jobs...\n");
        return 0;
    }
    else if(strcmp(comando,"cd") == 0){
        printf("cd...\n");
        return 0;
    }
    else if(strcmp(comando,"quit") == 0){
        exit(0);
    }
    
    return -1;
    
}

void rodarComando(char **argv){
    //char *local = strcat("/bin/",comando);
    execve(argv[0],argv,NULL);
}
