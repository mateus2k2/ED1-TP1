#include "tabuleiro.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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

void alocaTabuleiro(TADTabuleiro **Tabuleiro){
  
  *Tabuleiro = (TADTabuleiro*) malloc(sizeof(TADTabuleiro));

  if (*Tabuleiro == NULL ) {
    printf ("Memoria insuficiente !\n");
    exit (1);
  } 
}

void desalocaTabuleiro(TADTabuleiro **Tabuleiro) {
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

int** alocaMatriz(int lin, int col){
    int** mat;

    mat = malloc(lin * sizeof(int*));
    for (int i = 0; i < lin; i++)
        mat[i] = malloc(col * sizeof(int*));    

    if(mat == NULL)
        return NULL;

    return mat;
}

void desalocaMatriz(int **mat, int lin){
    for (int i = 0; i < lin; i++)
            free(mat[i]);
    free(mat);
}

void TabuleiroInicializa(char *nomeArquivo, TADTabuleiro* Tabuleiro){

  FILE* arquivo;
  int valor;
  char tmp;
  int cont = 0;

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

      if(valor >= 0 && valor <= 9)
        cont++;
      else {
        printf("Erro\n");
        exit(1);
      }
    }
  }
  if(cont != 81){
    printf("Erro\n");
    exit(1);
  }
}

int EhValido(TADTabuleiro* Tabuleiro, int lin, int col, int metodo){

  int retorno = 1;
  int cantoX = lin / 3 * 3;
  int cantoY = col / 3 * 3;

  //Verifica Linha
  if(metodo == 0 || metodo == 3){
    //Percorre toda a linha
    for (int i = 0; i < 9; i++){
      //Verifica a celula atual contra todas da regiao menos ela mesma e menos celulas ja marcadas como inválidas ou com 0 como conteudo
      if((*Tabuleiro).celulas[lin][i].conteudo == (*Tabuleiro).celulas[lin][col].conteudo && i != col 
        && (*Tabuleiro).celulas[lin][i].invalidoLinha != 1 && (*Tabuleiro).celulas[lin][i].conteudo != 0){
  
        if(metodo == 3) //Metodo 3 verifica linha, coluna e região ate encontra um único erro  
          return 0;
        //Se entrar no nesse if encontrou uma celula invalida então o retorno vai ser 0
        retorno = 0;
      }
    }
  }

  //Verifica coluna
  if(metodo == 1 || metodo == 3){
    //Percorre toda a coluna
    for (int i = 0; i < 9; i++){
      //Verifica a celula atual contra todas da regiao menos ela mesma e menos celulas ja marcadas como inválidas ou com 0 como conteudo
      if((*Tabuleiro).celulas[i][col].conteudo == (*Tabuleiro).celulas[lin][col].conteudo && i != lin 
        && (*Tabuleiro).celulas[i][col].invalidoColuna != 1 && (*Tabuleiro).celulas[i][col].conteudo != 0){
      
        if(metodo == 3) //Metodo 3 verifica linha, coluna e região ate encontra um único erro
          return 0;
        //Se entrar no nesse if encontrou uma celula invalida então o retorno vai ser 0
        retorno = 0;
      }
    }
  }

  //Verifica regiao
  if(metodo == 2 || metodo == 3){
    //Percorre toda a regiao
    for (int i = 0; i < 9; i++){
      //Verifica a celula atual contra todas da regiao menos ela mesma e menos celulas ja marcadas como inválidas ou com 0 como conteudo
      if((*Tabuleiro).celulas[cantoX + (i % 3)][cantoY + (i / 3)].conteudo == (*Tabuleiro).celulas[lin][col].conteudo //Verifica o conteudo
        && ((cantoX + (i % 3) != lin && cantoY + (i / 3) != col) || (cantoX + (i % 3) == lin && cantoY + (i / 3) != col) || (cantoX + (i % 3) != lin && cantoY + (i / 3) == col) ) //Garante que não vai verifica contra ele mesmo
        && (*Tabuleiro).celulas[cantoX + (i % 3)][cantoY + (i / 3)].invalidoRegiao != 1 && (*Tabuleiro).celulas[cantoX + (i % 3)][cantoY + (i / 3)].conteudo != 0){ // Garante que não esta repetidno
 
        if(metodo == 3) //Metodo 3 verifica linha, coluna e região ate encontra um único erro
          return 0;
        //Se entrar no nesse if encontrou uma celula invalida então o retorno vai ser 0
        retorno = 0;          
      }
    } 
  }

  return retorno;

}

int ValidaBoard(TADTabuleiro* Tabuleiro){

  int** CoordenadasInvalidas;
  int temInvalidas = 0;

  //Verifica se tem ao menos um erro no tabuleiro
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
        if(EhValido(Tabuleiro, i, j, 3) == 0){ 
            printf("Alguma coisa deu errado... Invalidos:\n");
            temInvalidas = 1;
            break;
        }
    }    
    if(temInvalidas == 1)
        break;
  }

  //Se nao tiver invalidas então retorna 1 e o tabuleiro é valido
  if(temInvalidas == 0)
    return 1;

  //Printar Problema na linha
  for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
          if(EhValido(Tabuleiro, i, j, 0) == 0){ //Se tiver problema na celula em relacao a linha
              CoordenadasInvalidas = encontraInvalidos(Tabuleiro, i, j, 0); //Encontrar todos os repetidos e armazenar na matrix [9][2] 
              PrintInvalidas(CoordenadasInvalidas, 0, i); //Printar todas as combinação dos repetidos
          }
      }        
  }     

  //Printar Problema na coluna
  for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
          if(EhValido(Tabuleiro, j, i, 1) == 0){ //Se tiver problema na celula em relacao a linha
              CoordenadasInvalidas = encontraInvalidos(Tabuleiro, j, i, 1); //Encontrar todos os repetidos e armazenar na matrix [9][2] 
              PrintInvalidas(CoordenadasInvalidas, 1, i); //Printar todas as combinação dos repetidos    
          }
      }        
  } 

  //Printar Problema na regiao
  for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
          if(EhValido(Tabuleiro, i, j, 2) == 0){ //Se tiver problema na celula em relacao a linha
              int cantoX = i / 3 * 3;
              int cantoY = j / 3 * 3;
              CoordenadasInvalidas = encontraInvalidos(Tabuleiro, i, j, 2); //Encontrar todos os repetidos e armazenar na matrix [9][2] 
              PrintInvalidas(CoordenadasInvalidas, 2 ,(cantoY/3) + (cantoX)); //Printar todas as combinação dos repetidos
          }
      }        
  }
  
  return 0;

}

int** encontraInvalidos(TADTabuleiro* Tabuleiro, int lin, int col, int metodo){
  //Alocacao da matriz com as coordenadas invalidas
  int **CoordenadasInvalidas;   
  CoordenadasInvalidas = alocaMatriz(9, 2);
  //Conta para percorer a regiao 
  int cantoX = lin / 3 * 3;
  int cantoY = col / 3 * 3;

  //Contador de invalidas
  int k = 0;
  
  //Passando pela linha
  if(metodo == 0){
    for (int i = 0; i < 9; i++){
      if((*Tabuleiro).celulas[lin][i].conteudo == (*Tabuleiro).celulas[lin][col].conteudo){ //Se os conteudos forem iguais
        //Marca a celula como invalida em relacao a linha
        (*Tabuleiro).celulas[lin][i].invalidoLinha = 1; 
        //Adiciona a coordenada na matriz de invalidas
        CoordenadasInvalidas[k][0] = lin; 
        CoordenadasInvalidas[k][1] = i;
        //Incrementa na quantidade de invalidas
        k++;
      }
    }
  }

  //Passando pela coluna
  if(metodo == 1){
    for (int i = 0; i < 9; i++){
      if((*Tabuleiro).celulas[i][col].conteudo == (*Tabuleiro).celulas[lin][col].conteudo){ //Se os conteudos forem iguais
        //Marca a celula como invalida em relacao a coluna
        (*Tabuleiro).celulas[i][col].invalidoColuna = 1;
        //Adiciona a coordenada na matriz de invalidas
        CoordenadasInvalidas[k][0] = i;
        CoordenadasInvalidas[k][1] = col;
        k++;
      }
    }
  }

  //Passando pela regiao
  if(metodo == 2){
    for (int i = 0; i < 9; i++){
      if((*Tabuleiro).celulas[cantoX + (i / 3)][cantoY + (i % 3)].conteudo == (*Tabuleiro).celulas[lin][col].conteudo){ //Se os conteudos forem iguais
        //Marca a celula como invalida em relacao a regiao
        (*Tabuleiro).celulas[cantoX + (i / 3)][cantoY + (i % 3)].invalidoRegiao = 1;
        //Adiciona a coordenada na matriz de invalidas
        CoordenadasInvalidas[k][0] = cantoX + (i / 3);
        CoordenadasInvalidas[k][1] = cantoY + (i % 3);
        //Incrementa na quantidade de invalidas
        k++;
      }
    } 
  }

  //Se nao encheu o matriz marcar o proxima linha com -1 
  if(k < 9){
    CoordenadasInvalidas[k][0] = -1;
    CoordenadasInvalidas[k][1] = -1;
  }
  
  return CoordenadasInvalidas;

}

void PrintInvalidas(int** CoordenadasInvalidas, int local, int numero){
  
  int quantidadeInvalidas=0;

  //Verifica a quantidade de coordenadas tem na matriz
  for (int i = 0; i < 9; i++){
    if(CoordenadasInvalidas[i][0] != -1)
      quantidadeInvalidas++;
    else  
      break;
  }  
  //No total será impressa a combinação de todas as coordenadas onde a ordem não importa e repetições nao são permitidas
  //Então para cada coordenada sera impressa ela com todas as posteiores
  for (int i = 0; i < quantidadeInvalidas; i++){
    for (int j = i+1; j < quantidadeInvalidas; j++){
      if(local == 0)
        printf("Linha %i: ", numero+1);
      if(local == 1)
        printf("Coluna %i: ", numero+1);
      if(local == 2)
        printf("Regiao %i: ", numero+1);

      printf("(%i, %i) e ", CoordenadasInvalidas[i][0]+1, CoordenadasInvalidas[i][1]+1);
      printf("(%i, %i)\n", CoordenadasInvalidas[j][0]+1, CoordenadasInvalidas[j][1]+1);
    }    
  }

  desalocaMatriz(CoordenadasInvalidas, 9);  

} 

int defineVazias(TADTabuleiro* Tabuleiro, int lin, int col){

  if(Tabuleiro->celulas[lin][col].conteudo == 0){
    return 1;
  }
  return 0;
}

void valoresValidos(TADTabuleiro* Tabuleiro){

  //Percorre toda a matriz 
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if(defineVazias(Tabuleiro, i, j) == 1){ //Se a célula é vazia
          printf("(%i, %i): ", i+1, j+1);
          for (int k = 1; k < 10; k++){ //Testar os valores de 1 a 9 nesse local
            //Supoe o valor nesse local
            (*Tabuleiro).celulas[i][j].conteudo = k;
            if(EhValido(Tabuleiro, i, j, 0) == 1 && EhValido(Tabuleiro, i, j, 1) == 1 && EhValido(Tabuleiro, i, j, 2) == 1)
              //Se for valido na linha, coluna e região ele é valido
              printf("%i ", k);
            //Volta a celula como 0
            (*Tabuleiro).celulas[i][j].conteudo = 0;
          }
          printf("\n");
      }
    }
  }
}

void imprimeTabuleiro(TADTabuleiro *tabuleiro){

  // for(int i = 0; i < 9; i++){
  //   if(i == 0){
  //     printf("    1 2 3   4 5 6   7 8 9\n   -----------------------\n");
  //   }
  //   for(int j = 0; j < 9; j++){
  //     if(j == 0){
  //       printf("%d | ", (i+1));
  //     }
  //     tabuleiro->celulas[i][j].conteudo == 0 ? printf("  ") : printf("%d ",tabuleiro->celulas[i][j].conteudo);
  //     if(j == 2 || j == 5 || j == 8){
  //       printf("| ");
  //     }
  //   }
  //   if(i == 2 || i == 5 || i == 8){
  //       printf("\n   -----------------------");
  //     }
  //   printf("\n");
  // }  

  for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
          printf("%i ", (*tabuleiro).celulas[i][j].conteudo);
      }
      printf("\n");        
  }
    
}