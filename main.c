#include "tabuleiro.h"

#include "solver.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
ARQUIVOS INTERMEDIÁRIOS
gcc -c tabuleiro.c tabuleiro.o -Wall
gcc -c main.c main.o -Wall
gcc -c solver.c solver.o -Wall
LINKAR ARQUIVOS
gcc tabuleiro.o main.o solver.o -o exe
EXECUTAR
./exe

COMPILAR TUDO DE UMA VEZ
gcc *.c -o exe
./exe
*/

int main(int argc, char *argv[]) {

    QTabuleiro *Tabuleiro;
    char *nomeArquivo;
    
    int temVazia = 0;
    int temInvalidas = 0;
    int reg; 

    int coodenadasInvalidas[9][2];
    int quantidadeInvalidas = 0;

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

    //Mostra tabuleiro
    imprimeTabuleiro(Tabuleiro);

    //Verificar se tem celulas vazias
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if(defineVazias(Tabuleiro, i, j) == 1)
                temVazia = 1;
        }
    }

    //Printar Mensagem de erro
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            valida(Tabuleiro, i, j, 3, &reg, &quantidadeInvalidas, coodenadasInvalidas);
            if(quantidadeInvalidas != 0){
                printf("Alguma coisa deu errado... Invalidos:\n");
                temInvalidas = 1;
                break;
            }
        }    
        if(quantidadeInvalidas != 0)
            break;;
    }

    quantidadeInvalidas = 0;

    //Printar Problema na linha
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            valida(Tabuleiro, i, j, 0, &reg, &quantidadeInvalidas, coodenadasInvalidas);
            if(quantidadeInvalidas != 0){
                printf("Linha %i: ", i+1);
                PrintInvalidas(quantidadeInvalidas, coodenadasInvalidas);      
            }
        }        
    }     

    //Printar Problema na coluna
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            valida(Tabuleiro, j, i, 1, &reg, &quantidadeInvalidas, coodenadasInvalidas);
            if(quantidadeInvalidas != 0){
                printf("Coluna %i: ", i+1);
                PrintInvalidas(quantidadeInvalidas, coodenadasInvalidas);      
            }
        }        
    } 

    //Printar Problema na regiao
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            valida(Tabuleiro, i, j, 2, &reg, &quantidadeInvalidas, coodenadasInvalidas);
            if(quantidadeInvalidas != 0){
                printf("Regiao %i: ", reg+1);
                PrintInvalidas(quantidadeInvalidas, coodenadasInvalidas);     
            }
        }        
    }  

    //Se não tiver Vazias ou Inválidas, printar sucesso
    if(temVazia == 0 && temInvalidas == 0){
        printf("Jogo completo. Voce ganhou!\n");
        return 0;
    }
    

    //Se não tiver inválidas e tiver vazias, printar sugestões
    if(temVazia == 1 && temInvalidas == 0){
        
        printSugestoes(Tabuleiro);

        //Resolver (Ponto Extra)
        if (solve(Tabuleiro))
            imprimeTabuleiro(Tabuleiro);
        else
            printf("\n\nNO SOLUTION FOUND\n\n");
            
    }

    //Desalocações
    desalocaTabuleiro(&Tabuleiro);
    desalocaNomeArquivo(&nomeArquivo);


    return 0;
    
}