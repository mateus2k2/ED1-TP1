#include "tabuleiro.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
ARQUIVOS INTERMEDIÁRIOS
gcc -c tabuleiro.c -Wall
gcc -c main.c -Wall
LINKAR ARQUIVOS
gcc tabuleiro.o main.o -o exe
EXECUTAR
./exe

COMPILAR TUDO DE UMA VEZ
gcc *.c -o exe
./exe
*/

int main(int argc, char *argv[]) {

    QTabuleiro *Tabuleiro;
    char *nomeArquivo;
    
    int temVazia;
    int quantidadeInvalidas = 0;
    int coodenadasInvalidas[9][2];
    int reg; 

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

    //Mostra p tabuleiro
    imprimeTabuleiro(Tabuleiro);

    //Verificar se tem celulas vazias
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(defineVazias(Tabuleiro, i, j) == 1)
                temVazia = 1;
        }
    }

    //Printar Problema na linha
    // for (int i = 0; i < 9; i++){
    //     for (int j = 0; j < 9; j++){
    //         valida(Tabuleiro, i, j, 0, &reg, &quantidadeInvalidas, coodenadasInvalidas);
    //         if(quantidadeInvalidas != 0){
    //             printf("Linha %i: ", i+1);
    //             PrintInvalidas(quantidadeInvalidas, coodenadasInvalidas);      
    //         }
    //     }        
    // }     

    // //Printar Problema na coluna
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            valida(Tabuleiro, i, j, 1, &reg, &quantidadeInvalidas, coodenadasInvalidas);
            if(quantidadeInvalidas != 0){
                printf("Coluna %i: ", j+1);
                PrintInvalidas(quantidadeInvalidas, coodenadasInvalidas);      
            }
        }        
    } 

    //Printar Problema na regiao
    // for (int i = 0; i < 9; i++){
    //     for (int j = 0; j < 9; j++){
    //         valida(Tabuleiro, i, j, 1, &reg, &quantidadeInvalidas, coodenadasInvalidas);
    //         if(quantidadeInvalidas != 0){
    //             printf("Regiao %i: ", reg+1);
    //             PrintInvalidas(quantidadeInvalidas, coodenadasInvalidas);     
    //         }
    //     }        
    // }  

    //Se não tiver Vazias ou Inválidas, printar sucesso
    
    //Se não tiver inválidas e tiver vazias, printar sugestões

    // //Problemas
    // desalocaTabuleiro(&Tabuleiro);
    // desalocaNomeArquivo(&nomeArquivo);


    return 0;
    
}