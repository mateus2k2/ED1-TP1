#include "tabuleiro.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct celula{
  //Estado | Estado em Relação a linha | Estado em Relação a coluna | Estado em Relação a região 
  //1  1 1 0  Invalido em relação a linha e a coluna
  //0  x x x  Valida
  //-1 x x x  Vazia
  int estado[4];
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

void alocaCelula(QCelula **Celula){
  *Celula = (QCelula*) malloc(sizeof(QCelula) * 9);

  if (*Celula == NULL ) {
    printf ("Memoria insuficiente !\n");
    exit (1);
  } 
}

void desalocacelula(QCelula **Celula){
  free(*Celula);
}

void TabuleiroInicializa(char *nomeArquivo, QTabuleiro* Tabuleiro){

  FILE* arquivo;
  int valor;
  char tmp;

  // Opening file in reading mode
  arquivo = fopen(nomeArquivo, "r");

  if (NULL == arquivo) {
      printf("Arquivo nao pode ser aberto\n");
      exit(1);
  }

  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      fscanf(arquivo, "%i", &valor);
      fscanf(arquivo, "%c", &tmp);
      (*Tabuleiro).celulas[i][j].conteudo = valor;
      (*Tabuleiro).celulas[i][j].estado[0] = 0;
      (*Tabuleiro).celulas[i][j].estado[1] = 0;
      (*Tabuleiro).celulas[i][j].estado[2] = 0;
      (*Tabuleiro).celulas[i][j].estado[3] = 0;

      //printf("%i ", (*Tabuleiro).celulas[i][j].conteudo);
    }
    //printf("\n");    
  }
  
}

int defineVazias(QTabuleiro* Tabuleiro, int lin, int col){

  if((*Tabuleiro).celulas[lin][col].conteudo == 0){
    (*Tabuleiro).celulas[lin][col].estado[0] = -1;
    return 1;
  }
  return 0;
}

int EhValido(QTabuleiro* Tabuleiro, int lin, int col, int metodo, QCelula* Conflitos){

  int k = 1, entrou = 0, retorno = 1;

  //Verifica Linha
  if(metodo == 0 && (*Tabuleiro).celulas[lin][col].estado[0] != 1){
    for (int j = 0; j < 9; j++){
      if(j != col && (*Tabuleiro).celulas[lin][col].conteudo == (*Tabuleiro).celulas[lin][j].conteudo && (*Tabuleiro).celulas[lin][j].estado[1] == 0){
        (Conflitos[k]).lin = lin;
        (Conflitos[k]).col = j;
        k++;

        (*Tabuleiro).celulas[lin][j].estado[0] = 1;
        (*Tabuleiro).celulas[lin][j].estado[1] = 1;

        entrou = 1;
      }
    }

    if(entrou == 1){
      printf("\nLinha %i: ", lin+1);

      (Conflitos[0]).lin = lin;
      (Conflitos[0]).col = col;

      (*Tabuleiro).celulas[lin][col].estado[0] = 1;
      (*Tabuleiro).celulas[lin][col].estado[1] = 1;

      retorno = 0;
    }

    (Conflitos[k+1]).lin = -1;
    (Conflitos[k+1]).col = -1;

    if(k != 1){
      for (int i = 0; i < k; i++){
        printf("(%i, %i)", Conflitos[i].lin+1, Conflitos[i].col+1);
        
        if ((Conflitos[i+2]).lin != -1)
          printf(" e ");
      } 
    }
  }
  
  //Verifica Coluna
  if(metodo == 1 && (*Tabuleiro).celulas[lin][col].estado[0] != -1){
    for (int j = 0; j < 9; j++){
      if(j != col && (*Tabuleiro).celulas[lin][col].conteudo == (*Tabuleiro).celulas[lin][j].conteudo && (*Tabuleiro).celulas[lin][j].estado[1] == 0){
        (Conflitos[k]).lin = lin;
        (Conflitos[k]).col = j;
        k++;

        (*Tabuleiro).celulas[lin][j].estado[0] = 1;
        (*Tabuleiro).celulas[lin][j].estado[1] = 1;

        entrou = 1;
      }
    }

    if(entrou == 1){
      printf("\nLinha %i: ", lin+1);

      (Conflitos[0]).lin = lin;
      (Conflitos[0]).col = col;

      (*Tabuleiro).celulas[lin][col].estado[0] = 1;
      (*Tabuleiro).celulas[lin][col].estado[1] = 1;

      retorno = 0;
    }

    (Conflitos[k+1]).lin = -1;
    (Conflitos[k+1]).col = -1;

    if(k != 1){
      for (int i = 0; i < k; i++){
        printf("(%i, %i)", Conflitos[i].lin+1, Conflitos[i].col+1);
        
        if ((Conflitos[i+2]).lin != -1)
          printf(" e ");
      } 
    }
  }

  //Verifica Região

  return retorno;

}
