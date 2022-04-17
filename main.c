#include "tabuleiro.h"

#include "solver.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
ARQUIVOS INTERMEDIÁRIOS
gcc -c tabuleiro.c -o tabuleiro.o -Wall
gcc -c main.c -o main.o -Wall
gcc -c solver.c -o solver.o -Wall
LINKAR ARQUIVOS
gcc tabuleiro.o main.o solver.o -o exe
EXECUTAR
./exe

COMPILAR TUDO DE UMA VEZ
gcc *.c -o exe -Wall
./exe
*/

int main(int argc, char *argv[]) {

    TADTabuleiro *Tabuleiro;
    char *nomeArquivo;
    
    int temVazia = 0;
    int temInvalidas = 0;

    //Aloca Tabuleiro
    alocaTabuleiro(&Tabuleiro);

    //Leitura e alocação nome do arquivo
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

    //Verifica se o tabuleiro inteiro é valido ou não
    if(ValidaBoard(Tabuleiro) == 0)
        temInvalidas = 1;
  
    //Se não tiver Vazias ou Inválidas, printar sucesso
    else if(temVazia == 0 && temInvalidas == 0){
        printf("Jogo completo. Voce ganhou!\n");
        return 0;
    }

    //Se não tiver inválidas e tiver vazias, printar sugestões  e solução
    else if(temVazia == 1 && temInvalidas == 0){
        
        //Printe Sugestões
        printf("Voce esta no caminho certo. Sugestoes:\n");
        valoresValidos(Tabuleiro);

        // sudokuSolv(Tabuleiro, 0, 0);
        // imprimeTabuleiro(Tabuleiro);

        //Resolver (Ponto Extra)
        if (resolve(Tabuleiro) == 0)
            printf("Erro\n");
        else
            imprimeTabuleiro(Tabuleiro);
    }
    
    //Desalocações
    desalocaTabuleiro(&Tabuleiro);
    desalocaNomeArquivo(&nomeArquivo);


    return 0;
    
}