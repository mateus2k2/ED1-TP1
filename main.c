#include "tabuleiro.h"
#include <stdio.h>
#include <string.h>

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
    int quantidadeInvalidas;

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

    //Função pra verificar se tem pelo menos 1 invalida e printar (Voce esta no caminho certo. Sugestoes:)

    //Printar Problema na linha
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            quantidadeInvalidas = EhValidoLinha(Tabuleiro, i, j);
            if(quantidadeInvalidas != 0){
                printf("Linha %i: ", i+1);
                PrintInvalidas(Tabuleiro, i, j, 0, quantidadeInvalidas);      
            }
        }        
    }     

    //Printar Problema na coluna
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            quantidadeInvalidas = EhValidoColuna(Tabuleiro, i, j);
            if(quantidadeInvalidas != 0){
                printf("Coluna %i: ", i+1);
                PrintInvalidas(Tabuleiro, i, j, 1, quantidadeInvalidas);      
            }
        }        
    } 

    //Printar Problema na linha
    // for (int i = 0; i < 9; i++){
    //     for (int j = 0; j < 9; j++){
    //         quantidadeInvalidas = EhValidoRegiao(Tabuleiro, i, j);
    //         if(quantidadeInvalidas != 0){
    //             printf("Regiao %i: ", i+1);
    //             PrintInvalidas(Tabuleiro, i, j, 2, quantidadeInvalidas);      
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