#include <stdio.h>
#include "tabuleiro.h"

struct celula{
  int conteudo;

  int invalidoLinha;
  int invalidoColuna;
  int invalidoRegiao;

};

struct tabuleiro{
  //Matriz de célula para compor o tabuleiro  
  struct celula celulas[9][9];
};

int validando(int number, TADTabuleiro* Tabuleiro, int linha, int coluna) {
    int i=0;

    int setorLinha = 3*(linha/3);
    int setorCol = 3*(coluna/3);
    
    int linha1 = (linha+2)%3;//variavel utilizada pra checar a primeira linha das 4 celulas restantes
    int linha2 = (linha+4)%3;//variavel utilizada pra checar a segunda linha das 4 celulas restantes
    
    int col1 = (coluna+2)%3;//variavel utilizada pra checar a primeira coluna das 4 celulas restantes
    int col2 = (coluna+4)%3;//variavel utilizada pra checar a segunda coluna das 4 celulas restantes
 
    /* Checa o valor da celula numa linha e coluna */
    for (i=0; i<9; i++) {
        if ((*Tabuleiro).celulas[i][coluna].conteudo == number) return 0;
        if ((*Tabuleiro).celulas[linha][i].conteudo == number) return 0;
    }
 
    /* Apos checar linha e coluna, serão 4 celulas restante que vão ser verificadas 
       usando as variaveis row1/row2 e col1/col2 
    */
    if((*Tabuleiro).celulas[linha1+setorLinha][col1+setorCol].conteudo == number) return 0;
    if((*Tabuleiro).celulas[linha2+setorLinha][col1+setorCol].conteudo == number) return 0;
    if((*Tabuleiro).celulas[linha1+setorLinha][col2+setorCol].conteudo == number) return 0;
    if((*Tabuleiro).celulas[linha2+setorLinha][col2+setorCol].conteudo == number) return 0;
    return 1;
}

int sudokuSolv(TADTabuleiro* Tabuleiro, int linha, int coluna){    

  int i = 1;

  for(i ; i < 10; i++){
     if(validando(i, Tabuleiro, linha, coluna)) {
           (*Tabuleiro).celulas[linha][coluna].conteudo = i;
            if (coluna == 8) {
                if (sudokuSolv(Tabuleiro, linha+1, 0)) return 1;
            } else {
                if (sudokuSolv(Tabuleiro, linha, coluna+1)) return 1;
            }
            (*Tabuleiro).celulas[linha][coluna].conteudo = 0;
        }
  }
  /*
    cada chamada dessa função passar pra proxima posição do tabuleiro
    depois de preencher um valor válido na celula
  */
  //-----------------------------------------------------------------------
  
    /*
        essa parte da função vai setar a condição de parada da função recursiva
    */

    if (9 == linha) {
        return 1;
        //Retorna 1 se chegar ate a ultima linha e tiver preenchido tudo
    }
 
    /*
    	Se o elemento ja estiver setado na celula faz uma
    	chamada recursiva pra proxima celula ate chegar na ultima.
    */

    if ((*Tabuleiro).celulas[linha][coluna].conteudo) {
        if (coluna == 8) {
            if (sudokuSolv(Tabuleiro, linha+1, 0)) return 1;
        } else {
            if (sudokuSolv(Tabuleiro, linha, coluna+1)) return 1;
        }
        return 0;
    }
    
}




