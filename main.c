#include "tabuleiro.h"
#include <stdio.h>
#include <string.h>

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
    char *nomeArquivo;
    int temVazia;

    //Aloca Tabuleiro
    alocaTabuleiro(&Tabuleiro);

    if(argc < 2){
        alocaNomeArquivo(&nomeArquivo, strlen("tabuleiro.txt"));
        strcpy(nomeArquivo, "tabuleiro.txt");
    }
    else{
        alocaNomeArquivo(&nomeArquivo, strlen(argv [1]));
        strcpy(nomeArquivo, argv[1]);
    }
    
    //Inicializa Tabuleiro como nome do arquivo do argv
    TabuleiroInicializa(nomeArquivo, Tabuleiro);

    //Verificar se tem celulas vazias
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(defineVazias(Tabuleiro, i, j) == 1)
                temVazia = 1;
        }
    }
    
    //Se encontrar invalida printar o problema
    printf("Alguma coisa deu errado... Invalidos:");
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(EhValido(Tabuleiro) == 0){
                
            }
        }        
    }    

    // //Se não tiver Vazias ou Inválidas, printar sucesso
    
    // //Se não tiver inválidas e tiver vazias, printar sugestões

    // //Problemas
    // desalocaTabuleiro(&Tabuleiro);
    // desalocaNomeArquivo(&nomeArquivo);

    printf("\n");

    return 0;
}