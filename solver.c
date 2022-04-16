//https://medium.com/@qwerty2323/sudoku-solver-c-recursive-implementation-backtracking-technique-415b42f9a24c

#include <stdio.h>
#include "tabuleiro.h"

struct celula{
  //conteudo da celula (int 1 a 9)
  int conteudo;

  int invalidoLinha;
  int invalidoColuna;
  int invalidoRegiao;

};

struct tabuleiro{
  //Matriz de célula para compor o tabuleiro  
  struct celula celulas[9][9];
};

int valida(TADTabuleiro* Tabuleiro, int linha, int coluna, int chute) {
  int cantoX = linha / 3 * 3;
  int cantoY = coluna / 3 * 3;

  for (int x = 0; x < 9; ++x) {
    if ((*Tabuleiro).celulas[linha][x].conteudo == chute) 
      return 0;
    if ((*Tabuleiro).celulas[x][coluna].conteudo == chute) 
      return 0;
    if ((*Tabuleiro).celulas[cantoX + (x % 3)][cantoY + (x / 3)].conteudo == chute) 
      return 0;
  }
  return 1;
}

int encontraVazias(TADTabuleiro* Tabuleiro, int *linha, int *coluna) {
  for (int x = 0; x < 9; x++) {
    for (int y = 0; y < 9; y++) {
      if (!(*Tabuleiro).celulas[x][y].conteudo) {
        *linha = x;
        *coluna = y;

        return 1;
      }
    }
  }
  return 0;
}

int resolve(TADTabuleiro* Tabuleiro) {
  int linha;
  int coluna;

  if(!encontraVazias(Tabuleiro, &linha, &coluna)) return 1;

  for (int chute = 1; chute < 10; chute++) {
    if (valida(Tabuleiro, linha, coluna, chute)) {
      (*Tabuleiro).celulas[linha][coluna].conteudo = chute;

      if(resolve(Tabuleiro)) return 1;
      (*Tabuleiro).celulas[linha][coluna].conteudo = 0;
    }
  }
  return 0;
}