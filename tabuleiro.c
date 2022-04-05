#include "tabuleiro.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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

//abstraire m uma unica funçao
int EhValidoLinha(QTabuleiro* Tabuleiro, int lin, int col){

  int retorno = 0;  

  for (int i = 0; i < 9; i++){
    if((*Tabuleiro).celulas[lin][i].conteudo == (*Tabuleiro).celulas[lin][col].conteudo && i != col && (*Tabuleiro).celulas[lin][i].invalidoLinha != 1 && (*Tabuleiro).celulas[lin][i].conteudo != 0){
      (*Tabuleiro).celulas[lin][i].invalidoLinha = 1;
      retorno++;
    }
  
  }

  if(retorno != 0)
    (*Tabuleiro).celulas[lin][col].invalidoLinha = 1;

  return retorno;
  
}

int EhValidoColuna(QTabuleiro* Tabuleiro, int lin, int col){

  int retorno = 0;  

  for (int i = 0; i < 9; i++){
    if((*Tabuleiro).celulas[i][col].conteudo == (*Tabuleiro).celulas[lin][col].conteudo && i != lin && (*Tabuleiro).celulas[i][col].invalidoColuna != 1){
      (*Tabuleiro).celulas[i][col].invalidoColuna = 1;
      retorno++;
    }
  }

  if(retorno != 0)
    (*Tabuleiro).celulas[lin][col].invalidoColuna = 1;

  return retorno;
  
}

int EhValidoRegiao(QTabuleiro* Tabuleiro, int lin, int col){
  
  // int retorno = 0;  

  // for (int i = 0; i < 9; i++){
  //   if((*Tabuleiro).celulas[lin][i].conteudo == (*Tabuleiro).celulas[lin][col].conteudo && i != col && (*Tabuleiro).celulas[lin][i].invalidoLinha != 1){
  //     (*Tabuleiro).celulas[lin][i].invalidoLinha = 1;
  //     retorno++;
  //   }
  // }

  // if(retorno != 0)
  //   (*Tabuleiro).celulas[lin][col].invalidoLinha = 1;

  // return retorno;
}

void PrintInvalidas(QTabuleiro* Tabuleiro, int lin, int col, int metodo, int quantidadeInvalidas){

  int invalidasEncontras = 0;

  //Verifica Linha
  if(metodo == 0){
    for (int i = 0; i < 9; i++){
      if( (*Tabuleiro).celulas[lin][i].conteudo == (*Tabuleiro).celulas[lin][col].conteudo ){
        printf("(%i, %i)", lin+1, i+1);
        invalidasEncontras++;

        if(invalidasEncontras - 1 == quantidadeInvalidas){
          printf("\n");
          break;
        }

        else
          printf(" e ");
      }

    }
  }

  //Verifica Coluna
  if(metodo == 1){
    for (int i = 0; i < 9; i++){
      if( (*Tabuleiro).celulas[i][col].conteudo == (*Tabuleiro).celulas[lin][col].conteudo ){
        printf("(%i, %i)", i+1, col+1);
        invalidasEncontras++;

        if(invalidasEncontras - 1 == quantidadeInvalidas){
          printf("\n");
          break;
        }
        else
          printf(" e ");
      }
    }
  }

  //Verifica Região


}      