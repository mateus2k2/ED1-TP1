#include "tabuleiro.h"
#include <stdio.h>
#include <string.h>

/*
DUVIDAS
Tratas casos de erros
Arrumar funções
*/

/*
gcc -c tabuleiro.c -Wall
gcc -c main.c -Wall
gcc tabuleiro.o main.o -o exe
./exe < Casos/1.in

gcc *.c -o exe
./exe
*/

int main(int argc, char *argv[]) {

    QTabuleiro *Tabuleiro;
    QCelula *CelulasInvalidas;
    char *nomeArquivo;
    int temVazia;

    //Aloca Tabuleiro
    alocaTabuleiro(&Tabuleiro);
    //Aloca vetor de 9 celulas (maximo de conflidos por numero
    alocaCelula(&CelulasInvalidas);

    if(argc < 2){
        alocaNomeArquivo(&nomeArquivo, strlen("tabuleiro.txt"));
        strcpy(nomeArquivo, "tabuleiro.txt");

        //printf("Uso : %s %s\n", argv [0], nomeArquivo);
    }
    else{
        alocaNomeArquivo(&nomeArquivo, strlen(argv [1]));
        strcpy(nomeArquivo, argv[1]);

        //printf("Uso : %s %s\n", argv [0], nomeArquivo);
    }
    
    //Inicializa Tabuleiro como nome do arquivo do argv
    TabuleiroInicializa(nomeArquivo, Tabuleiro);

    //Verificar as celulas vazias
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(defineVazias(Tabuleiro, i, j) == 1)
                temVazia = 1;
        }
    }
    
    
    // 0 linha 1 coluna 3 região
    int metodo = 0, erro = 0;

    //Se encontrar 1 invaliza printar a invalidade
    //Forma de dar esse print 1 vez se encontrar uma invalidade
    //Dividir EhValido em mais funções
    printf("Alguma coisa deu errado... Invalidos:");
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(EhValido(Tabuleiro, i, j, metodo, CelulasInvalidas) == 0){
                
            }
        }        
    }    

    // //Se nao encontra invalida printar sucesso se não tiver vazias
    // if (temVazia = 0)
    //     printf("\nJogo completo. Voce ganhou!");
    
    // //Se nao encontra invalida printar sugestões para as vazias
    // if (temVazia = 1){
    //     printf("\nVoce esta no caminho certo. Sugestoes:");
    //     valoresValidos(Tabuleiro);
    // }

    //Problemas
    // desalocaTabuleiro(&Tabuleiro);
    // desalocaNomeArquivo(&nomeArquivo);
    // desalocaNomeArquivo(&CelulasInvalidas);

    printf("\n");

    return 0;
}