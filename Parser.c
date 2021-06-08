#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Parser.h"

/*
* Esta função divide o texto do comando em um array de strings
* Esse array de strings vai ser o argv para o execve 
* Lembrar: Dar free() quando usar essa função 
*/
char  **criarArgv(char *comando, int *recebedorQuantidade){
    /* TODO: Colocar um parametro do tipo ponteiro para inteiro para ter a informação a respeito do número de elementos
        Isso vai ser importante para acessar o último item(avaliar se é ou não é "&") */
     
    char **argv;
    char *tokenDosElementos;
    int quantidadeElementos = 0;
    // Isso é necessário, porque quando eu usar strtok, o resultado vai ser char*, mas eu preciso de **char
    // eu também preciso de um vetor de strings que possua o ultimo argumento como null

    argv = malloc(sizeof(char *));
    if(argv){ // se a alocação deu certo
        tokenDosElementos = strtok(comando," "); // "separa" elementos com delimitação baseada em espaço

        while(tokenDosElementos != NULL){
            argv = realloc(argv,sizeof(char *) * (quantidadeElementos+1));
            if(argv){ // caso a alocação tiver sucesso
                argv[quantidadeElementos] = tokenDosElementos;
                tokenDosElementos = strtok(NULL," "); // passa pro próximo pedaço da string separado por espaço
                quantidadeElementos++;
            }
            else{ // senão
                printf("Erro na alocação :(\n");
                exit(1);
            }
        }
        // Colocar NULL como último elemento do vetor de string é importante para o uso
        // da função execve,que exige que o último elemento seja NULL
        argv = realloc(argv,sizeof(char *) * (quantidadeElementos+1));
        if(argv == NULL){ // se a alocação deu problema 
            printf("erro na alocação :(\n");
            exit(1);
        }
        else{ // se a alocação deu certo
            argv[quantidadeElementos] = NULL;
            // Aqui eu atualizo o valor do ponteiro pra inteiro que vai ter a quantidade de elementos em argv
            // isso vai ser necessário para acessar o último item
            
            if(recebedorQuantidade != NULL){
                quantidadeElementos++;
                *recebedorQuantidade = quantidadeElementos;
            }
        }


    }else{
        printf("erro na alcalçao :(\n");
    }

    return argv;
}


/*
* Quando recebemos entrada com o fgets(), ele captura o newline (\n) 
* e coloca no fim da string. Essa função so remove esse newline para
* facilitar ao usar strcmp().
* 
*/
void removerNewLineDaString(char *texto){
    int tamanhoDoTexto = strlen(texto);
    if(tamanhoDoTexto > 1){ // se a string não estiver vazia
        texto[tamanhoDoTexto -1] = '\0';
    }
}

/*
* Faz a concatenação de string entre a localização /bin/ + comando 
*
*/
void criarTextoDoComando(char *destino,char *binFolder, char *comando){
    strcpy(destino,binFolder);
    strcat(destino,comando);
}

/*
*   Verifica se o processo deverá ser feito em background.
*   Retorna 1 se for um processo background. Retorna 0 se não for
*/
int isBackgroundProcess(char *type){
    if(strcmp(type,"&") == 0){
        return 1;
    } else{
        return 0;
    }
}