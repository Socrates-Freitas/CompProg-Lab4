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
#include "Builtin.h"
#define MAX_INPUT_SIZE 150


void printShell();
void commandRunner();
int handleBuiltIn(char** argv);

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
        builtInType = handleBuiltIn(argv);
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

int handleBuiltIn(char** argv){
    if(strcmp(argv[0],"fg") == 0){
        printf("fg...\n");
        return 0;
    }
    else if(strcmp(argv[0],"bg") == 0 ){
        printf("bg...\n");
        return 0;
    }
    else if(strcmp(argv[0],"jobs") == 0 ){
        printf("jobs...\n");
        return 0;
    }
    else if(strcmp(argv[0],"cd") == 0){
        builtIn_cd(argv[1]);
        return 0;
    }
    else if(strcmp(argv[0],"quit") == 0){
        exit(0);
    }
    else if(strcmp(argv[0],"help") == 0){
	    puts("\nList of Commands supported:"
	        "cd - Change the current working directory"
            "fg - Bring a background process to the foreground"
            "quit - This will quit the shell"
	        "bg - Runs jobs in the background"
	        "jobs... - Show the active jobs in shell");
        return 0;
    }
    
    return -1;
    
}


