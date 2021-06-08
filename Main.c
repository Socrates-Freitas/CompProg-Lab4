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
#include "Main.h"
#include "Parser.h"
#include "Builtin.h"


#define MAX_INPUT_SIZE 150
#define NUMERO_ATE_ULTIMO_ITEM_ARGV 2  



int main(int argc, char **argv){
    while(1){
        signal(SIGINT,SIG_IGN);
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
    if(entrada[0] == '\n'){// se entrada estiver vazia
        return; // sai da função e vai pra proxima iteração do loop
    } 

    removerNewLineDaString(entrada); // retira o \n no final da string de entrada
    if(feof(stdin)){ // Ctr + D
        printf("\n");
        exit(0);
    }

    argv = criarArgv(entrada,&numeroDeElementos);
    if(argv){
        builtInType = handleBuiltIn(argv);
        if(builtInType == -1){ // se não for built in
            pid = fork();
            if(pid == 0){
                signal(SIGINT,SIG_DFL);
                int falhaExecucao; // Indicará se a execução de execve falhou
                // Aqui subtrai por 2 porque o último(numeroDeElementos) elemento é NULL
                isBackground = isBackgroundProcess(argv[numeroDeElementos - NUMERO_ATE_ULTIMO_ITEM_ARGV]); 

                if(isBackground != 0){
                // printf("é sim\n");
                }
                else{
                    //printf("num e nao\n");
                }

                criarTextoDoComando(comandoConcatenado,binFolder,argv[0]);

                falhaExecucao = execve(comandoConcatenado,argv,__environ);
                if(falhaExecucao != 0){ // se houve falha na execução de um comando pelo execve...
                    fprintf(stderr,"Comando inválido\n");
                }
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
    else if(strcmp(argv[0],"exit") == 0){
        exit(0);
    }
    else if(strcmp(argv[0],"^C") == 0){
        exit(0);
    }
    else if(strcmp(argv[0],"help") == 0){
	    puts("Lista de comandos suportados:\n"
	        "cd - Mudar o diretório atual\n"
            "fg - Trazer processo em background para foreground\n"
            "exit - Este comando irá terminar a shell\n"
	        "bg - Executa programas em background\n"
	        "jobs - Exibe os programas ativos na shell");
        return 0;
    }
    
    return -1;
    
}


