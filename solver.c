#include "tabuleiro.h"

#include <stdio.h>

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

/*
1. Encontra uma célula Vazia.
  1.1. Se não tem Nenhuma Célula Vazia retornar.
2. Encontrar sugestões válidas para uma célula vazia
  2.1. Resolver o problema recursivamente com essas sugestões.
    2.1.1. Se não tem sugestões válidas, "marcar" a célula como 0 e a determinado "ramo" como sem fim (). (backtracking)
*/

//Verifica o valor "Chutado" em uma dada posicao
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

//Retorna 1 se encontrar vazias e 0 se não encontrar
//Modifica linha e coluna com as coordenadas vazias encontradas 
int encontraVazias(TADTabuleiro* Tabuleiro, int *linha, int *coluna) {
  for (int x = 0; x < 9; x++) {
    for (int y = 0; y < 9; y++) {
      if ((*Tabuleiro).celulas[x][y].conteudo == 0) {
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

  //Pega a primeira/proxima coordenada de uma célula vazia
  if(encontraVazias(Tabuleiro, &linha, &coluna) == 0) 
    return 1; //Se nao tiver vazias retorna 1

  for (int chute = 1; chute < 10; chute++) {
    //Testa os valores de 1 a 9
    if (valida(Tabuleiro, linha, coluna, chute)) {
      //Se o valor for valido nessa celula então ele e substituido
      (*Tabuleiro).celulas[linha][coluna].conteudo = chute;

      if(resolve(Tabuleiro) == 1) 
        return 1; //Se nao tiver vazias retorna 1

      //Se ainda tiver vazias volta a celula como 0      
      (*Tabuleiro).celulas[linha][coluna].conteudo = 0;
    }
  }

  //Se tudo for testado e chegou nesse ponto entao nao tem soução para esse sudoku
  return 0;
}