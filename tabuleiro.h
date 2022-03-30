#ifndef ALUNO_H
#define ALUNO_H

// typedef struct aluno TAluno;
// typedef struct turma TTurma;

typedef struct celula QCelula;
typedef struct quadrante Qquadrante;
typedef struct tabuleiro QTabuleiro;


void alocaTabuleiro(QTabuleiro**);
void desalocaTabuleiro(QTabuleiro**);

void alocaNomeArquivo(char **nomeArquivo, int qtd);
void desalocaNomeArquivo(char **nomeArquivo);

void alocaCelula(QCelula **Celula);
void desalocacelula(QCelula **Celula);

void imprimeTabuleiro(QTabuleiro*);

//inicializa tabuleiro a partir de arquivo
void TabuleiroInicializa(char *nomeArquivo, QTabuleiro*);

// //retorna célula vazias do tabuleiro.
int defineVazias(QTabuleiro*, int lin, int col);

//verifica se uma célula é válida.
int EhValido(QTabuleiro*); 

// retorna todos os valores válidos para uma célula vazia.
int* valoresValidos(QTabuleiro*);



#endif //ALUNO_H