#ifndef TabuleiroH
#define TabuleiroH

// typedef struct aluno TAluno;
// typedef struct turma TTurma;

typedef struct celula QCelula;
typedef struct tabuleiro QTabuleiro;
typedef struct coordenada QCoordenada;


void alocaTabuleiro(QTabuleiro**);
void desalocaTabuleiro(QTabuleiro**);

void alocaNomeArquivo(char **nomeArquivo, int qtd);
void desalocaNomeArquivo(char **nomeArquivo);

int** alocaMatriz(int lin, int col);
void desalocaMatriz(int **mat, int lin);

void TabuleiroInicializa(char *nomeArquivo, QTabuleiro*);

int verificaCelula(QTabuleiro* Tabuleiro, int lin, int col, int metodo);

int EhValido(QTabuleiro* Tabuleiro);
int** encontraInvalidos(QTabuleiro* Tabuleiro, int lin, int col, int metodo);
void PrintInvalidas(int** CoordenadasInvalidas, int local, int numero);

int defineVazias(QTabuleiro*, int lin, int col);
void printSugestoes(QTabuleiro* tabuleiro);


void imprimeTabuleiro(QTabuleiro *tabuleiro);

#endif //TabuleiroH