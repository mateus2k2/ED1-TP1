#include "tabuleiro.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct celula{
  //conteudo da celula (int 1 a 9)
  int conteudo;
  //posicao
  int lin, col;
};

struct tabuleiro{
  //Matriz de célula para compor o tabuleiro  
  struct celula celulas[9][9];
};

void alocaTabuleiro(QTabuleiro **Tabuleiro){
  
  *Tabuleiro = (QTabuleiro*) malloc(sizeof(QTabuleiro));

  if (*Tabuleiro == NULL ) {
    printf ("Memoria insuficiente !\n");
    exit (1);
  } 
}

void desalocaTabuleiro(QTabuleiro **Tabuleiro) {
  free(*Tabuleiro);
}

void alocaNomeArquivo(char **nomeArquivo, int qtd){
  *nomeArquivo = (char*) malloc(sizeof(char)*qtd);

  if (*nomeArquivo == NULL ){
    printf ("Memoria insuficiente !\n");
    exit (1);
  } 
}

void desalocaNomeArquivo(char **nomeArquivo){
  free(*nomeArquivo);
}

void TabuleiroInicializa(char *nomeArquivo, QTabuleiro* Tabuleiro){

  FILE* arquivo;
  int valor;
  char tmp;

  arquivo = fopen(nomeArquivo, "r");

  if (NULL == arquivo) {
      printf("Arquivo nao pode ser aberto\n");
      exit(1);
  }

  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      fscanf(arquivo, "%d%c", &valor, &tmp);
    
      (*Tabuleiro).celulas[i][j].conteudo = valor;
      
    }
  }
  
}

int defineVazias(QTabuleiro* Tabuleiro, int lin, int col){

  if((*Tabuleiro).celulas[lin][col].conteudo == 0){
    // (*Tabuleiro).celulas[lin][col].estado[0] = -1;
    return 1;
  }
  return 0;
}

void imprimeTabuleiro(QTabuleiro *tabuleiro){

  for(int i = 0; i < 9; i++){
    if(i == 0){
      printf("   1 2 3   4 5 6   7 8 9\n   -----------------------\n");
    }
    for(int j = 0; j < 9; j++){
      if(j == 0){
        printf("%d | ", (i+1));
      }
      printf("%d ",(*tabuleiro).celulas[i][j].conteudo);
      if(j == 2 || j == 5 || j == 8){
        printf("| ");
      }
    }
    if(i == 2 || i == 5 || i == 8){
        printf("\n   -----------------------");
      }
    printf("\n");
  }
}


int EhValido(QTabuleiro* Tabuleiro){
  
}

