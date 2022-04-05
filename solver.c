//https://medium.com/@qwerty2323/sudoku-solver-c-recursive-implementation-backtracking-technique-415b42f9a24c

#include <stdio.h>
#include "tabuleiro.h"

struct celula{
  //conteudo da celula (int 1 a 9)
  int conteudo;
  int regiao;

  int invalidoLinha;
  int invalidoColuna;
  int invalidoRegiao;

};

struct tabuleiro{
  //Matriz de célula para compor o tabuleiro  
  struct celula celulas[9][9];
};

int valid(QTabuleiro* Tabuleiro, int row, int column, int guess) {
  int corner_x = row / 3 * 3;
  int corner_y = column / 3 * 3;

  for (int x = 0; x < 9; ++x) {
    if ((*Tabuleiro).celulas[row][x].conteudo == guess) return 0;
    if ((*Tabuleiro).celulas[x][column].conteudo == guess) return 0;
    if ((*Tabuleiro).celulas[corner_x + (x % 3)][corner_y + (x / 3)].conteudo == guess) return 0;
  }
  return 1;
}

int find_empty_cell(QTabuleiro* Tabuleiro, int *row, int *column) {
  for (int x = 0; x < 9; x++) {
    for (int y = 0; y < 9; y++) {
      if (!(*Tabuleiro).celulas[x][y].conteudo) {
        *row = x;
        *column = y;

        return 1;
      }
    }
  }
  return 0;
}

int solve(QTabuleiro* Tabuleiro) {
  int row;
  int column;

  if(!find_empty_cell(Tabuleiro, &row, &column)) return 1;

  for (int guess = 1; guess < 10; guess++) {
    if (valid(Tabuleiro, row, column, guess)) {
      (*Tabuleiro).celulas[row][column].conteudo = guess;

      if(solve(Tabuleiro)) return 1;
      (*Tabuleiro).celulas[row][column].conteudo = 0;
    }
  }
  return 0;
}