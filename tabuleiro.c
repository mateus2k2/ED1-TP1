#include "tabuleiro.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct celula{
  //conteudo da celula (int 1 a 9)
  int conteudo;
  int regiao;

  int invalidoLinha;
  int invalidoColuna;
  int invalidoRegiao;

  int verifica [9];
  int contadorValida;


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

  //Abre o arquivo
  arquivo = fopen(nomeArquivo, "r");

  if (NULL == arquivo){
      //Se nao for possivel encerra o programa
      printf("Arquivo nao pode ser aberto\n");
      exit(1);
  }

  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      //Le o valor (em valor) e o espaço (em tmp)
      fscanf(arquivo, "%d%c", &valor, &tmp);
    
      (*Tabuleiro).celulas[i][j].conteudo = valor;
      
    }
  }
}

int defineVazias(QTabuleiro* Tabuleiro, int lin, int col){

  if(Tabuleiro->celulas[lin][col].conteudo == 0){
    return 1;
  }
  return 0;
}

void imprimeTabuleiro(QTabuleiro *tabuleiro){

  for(int i = 0; i < 9; i++){
    if(i == 0){
      printf("    1 2 3   4 5 6   7 8 9\n   -----------------------\n");
    }
    for(int j = 0; j < 9; j++){
      if(j == 0){
        printf("%d | ", (i+1));
      }
      tabuleiro->celulas[i][j].conteudo == 0 ? printf("  ") : printf("%d ",tabuleiro->celulas[i][j].conteudo);
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

void valida(QTabuleiro* Tabuleiro, int lin, int col, int metodo, int *reg, int *quantidadeInvalidas, int coodenadasInvalidas[9][2]){

  (*quantidadeInvalidas) = 0;
  int offset[9][2] = {{0,0}, {0,3}, {0, 6}, {3, 0}, {3, 3}, {3, 6}, {6,0}, {6,3}, {6,6}};

  //Metodo 3 = verifica se tem ao menos 1 erro

  //Valida Linha
  if(metodo == 0 || metodo == 3){
    //Percorre toda a linha
    for (int i = 0; i < 9; i++){
      //Verifica a celula atual contra todas da linha menos ela mesma
      if((*Tabuleiro).celulas[lin][i].conteudo == (*Tabuleiro).celulas[lin][col].conteudo && i != col && 
        (*Tabuleiro).celulas[lin][i].invalidoLinha != 1 && (*Tabuleiro).celulas[lin][i].conteudo != 0){
          
        //Preenche o vetor de invalidas. Deixa a primeira posição vazia
        coodenadasInvalidas[(*quantidadeInvalidas)+1][0] = lin;
        coodenadasInvalidas[(*quantidadeInvalidas)+1][1] = i;

        (*quantidadeInvalidas)++;

        if(metodo == 3)
          break;        

        //Marca como invalida para não verificar essa posição novamente
        (*Tabuleiro).celulas[lin][i].invalidoLinha = 1;
        
      }
    }

  }

  //Valida Coluna
  if(metodo == 1 || metodo == 3){
    //Percorre toda a coluna
    for (int i = 0; i < 9; i++){
      //Verifica a celula atual contra todas da coluna menos ela mesma
      if((*Tabuleiro).celulas[i][col].conteudo == (*Tabuleiro).celulas[lin][col].conteudo && i != lin && 
        (*Tabuleiro).celulas[i][col].invalidoColuna != 1 && (*Tabuleiro).celulas[i][col].conteudo != 0){
      
        //Preenche o vetor de invalidas. Deixa a primeira posição vazia
        coodenadasInvalidas[(*quantidadeInvalidas)+1][0] = i;
        coodenadasInvalidas[(*quantidadeInvalidas)+1][1] = col;

        (*quantidadeInvalidas)++;

        if(metodo == 3)
          break;

        //Marca como invalida para não verificar essa posição novamente
        (*Tabuleiro).celulas[i][col].invalidoColuna = 1;

      }
    }
  }

  //Verifica Região
  if(metodo == 2 || metodo == 3){
    //verificar em qual região esta
    if(lin < 3 && col < 3)
      (*reg) = 0;
    else if(lin < 3 && col >= 3 && col < 6)
      (*reg) = 1;
    else if(lin < 3 && col >= 6)
      (*reg) = 2;
    else if(lin >= 3 && lin < 6 && col < 3)
      (*reg) = 3;
    else if(lin >= 3 && lin < 6 && col >= 3 && col <= 5)
      (*reg) = 4;
    else if(lin >= 3 && lin < 6 && col >= 6)
      (*reg) = 5;
    else if(lin >= 6 && col < 3)
      (*reg) = 6;
    else if(lin >= 6 && col >= 3 && col < 6)
      (*reg) = 7;
    else if(lin >= 6 && col >= 6)
      (*reg) = 8;

    //Preenche o campo região com reg (0 a 8)
    (*Tabuleiro).celulas[lin][col].regiao = (*reg);

    //Percorre toda a região. Começando de acordo com qual região esta e indo 3 posições a mais
    for (int j = offset[(*reg)][0]; j < offset[(*reg)][0]+3; j++){
      for (int k = offset[(*reg)][1]; k < offset[(*reg)][1]+3; k++){
        //Verifica a celula atual contra todas da região menos ela mesma
        if((*Tabuleiro).celulas[j][k].conteudo == (*Tabuleiro).celulas[lin][col].conteudo && ((j != lin && k != col) || (j == lin && k != col) || (j != lin && k == col) ) 
          && (*Tabuleiro).celulas[j][k].invalidoRegiao != 1 && (*Tabuleiro).celulas[j][k].conteudo != 0){
          
          //Preenche o vetor de invalidas. Deixa a primeira posição vazia
          coodenadasInvalidas[(*quantidadeInvalidas)+1][0] = j;
          coodenadasInvalidas[(*quantidadeInvalidas)+1][1] = k;          

          (*quantidadeInvalidas)++;
          
          if(metodo == 3)
            break;

          //Marca como invalida para não verificar essa posição novamente
          (*Tabuleiro).celulas[j][k].invalidoRegiao = 1;
          
        }
      }
    } 
  }

  //Verificação para Todos. Entra se encontrou um invalida
  if(*quantidadeInvalidas != 0){
    //Coloca a celula atual na primeira posição do vetor de invalidas
    coodenadasInvalidas[0][0] = lin;
    coodenadasInvalidas[0][1] = col;

    //Marca ela como invalida na linha, coluna ou região
    if(metodo == 0)
      (*Tabuleiro).celulas[lin][col].invalidoLinha = 1;
    else if(metodo == 1)
      (*Tabuleiro).celulas[lin][col].invalidoColuna = 1;
    else if (metodo == 2)
      (*Tabuleiro).celulas[lin][col].invalidoRegiao = 1;

    (*quantidadeInvalidas)++;
  }

}

void PrintInvalidas(int quantidadeInvalidas, int coodenadasInvalidas[9][2]){
  
  //Printar Linha
  for (int i = 0; i < 9; i++){
    printf("(%i, %i)", (coodenadasInvalidas)[i][0]+1, (coodenadasInvalidas)[i][1]+1);

    //Se for a ultima print um /n e não print um "e"
    if(i + 1 == quantidadeInvalidas){
      printf("\n");
      break;
    }
    else
      printf(" e ");
  }

} 

void printSugestoes(QTabuleiro* tabuleiro){

  printf("\nVoce esta no caminho certo. Sugestoes:\n");

  int contadorVazias = 0, **coordVazias;
  int i, j;
  //verificando quantas casa estao vazias para alocar a matriz de cordenadas vazias
  for (i = 0; i < 9; i++){
    for(j = 0; j < 9; j++){
      if(defineVazias(tabuleiro, i, j) == 1){
        contadorVazias++;
      }
    }
    // else
    //   printf(" e ");
  }


  //alocando a matriz de cordenadas vazias
  coordVazias = (int**)malloc(contadorVazias * sizeof(int *));
  for(i = 0; i<contadorVazias; i++){
    coordVazias[i] = (int*)malloc(2 * sizeof(int));
  }


  //preenchendo o vetor com as coordenadas vazias
  int cont = 0;
  for (i = 0; i < 9; i++){
    for(j = 0; j < 9; j++){
      if(defineVazias(tabuleiro, i, j) == 1){
        coordVazias[cont][0] = i;
        coordVazias[cont][1] = j;
        cont++;
      }
    }
  }

  //verificando os numeros pissiveis
  int result = 0;
  for(i = 0; i < contadorVazias; i++){
    printf("(%d,%d): ",coordVazias[i][0] + 1,coordVazias[i][1] + 1);

    //verificando linha
    for(int coluna = 0; coluna < 9; coluna++){
      result = (tabuleiro->celulas[coordVazias[i][0]][coluna].conteudo - 1);
      if(result >= 0)     
        tabuleiro->celulas[coordVazias[i][0]][coordVazias[i][1]].verifica[result] = 0;
      else
        tabuleiro->celulas[coordVazias[i][0]][coordVazias[i][1]].verifica[result] = 1;
    }
    //verificando coluna
    for(int linha = 0; linha < 9; linha ++){
      result = (tabuleiro->celulas[linha][coordVazias[i][1]].conteudo - 1);
      if(result >= 0)
        tabuleiro->celulas[coordVazias[i][0]][coordVazias[i][1]].verifica[result] = 0;
      else
        tabuleiro->celulas[coordVazias[i][0]][coordVazias[i][1]].verifica[result] = 1;
    }
    //verificando regiao
    for(int linha = 0; linha < 9; linha ++){
      for (int coluna = 0; coluna < 9; coluna++){
        if(tabuleiro->celulas[linha][coluna].regiao ==  tabuleiro->celulas[coordVazias[i][0]][coordVazias[i][1]].regiao){
          result = (tabuleiro->celulas[linha][coluna].conteudo - 1);
          if(result >= 0)
            tabuleiro->celulas[coordVazias[i][0]][coordVazias[i][1]].verifica[result] = 0;
          else
            tabuleiro->celulas[coordVazias[i][0]][coordVazias[i][1]].verifica[result] = 1;
        }
      }
    }

    //printando o resultado
    for(int livre = 0; livre < 9; livre++){
      if(tabuleiro->celulas[coordVazias[i][0]][coordVazias[i][1]].verifica[livre] != 0){
        printf("%d ", livre+1);
      }
    }
    printf("\n");
  }
}