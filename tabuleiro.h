#ifndef TabuleiroH
#define TabuleiroH

// typedef struct aluno TAluno;
// typedef struct turma TTurma;

typedef struct celula TADCelula;
typedef struct tabuleiro TADTabuleiro;

void alocaTabuleiro(TADTabuleiro**);
void desalocaTabuleiro(TADTabuleiro**);

void alocaNomeArquivo(char **nomeArquivo, int qtd);
void desalocaNomeArquivo(char **nomeArquivo);

int** alocaMatriz(int lin, int col);
void desalocaMatriz(int **mat, int lin);

void TabuleiroInicializa(char *nomeArquivo, TADTabuleiro*);

int verificaCelula(TADTabuleiro* Tabuleiro, int lin, int col, int metodo);

int EhValido(TADTabuleiro* Tabuleiro);
int** encontraInvalidos(TADTabuleiro* Tabuleiro, int lin, int col, int metodo);
void PrintInvalidas(int** CoordenadasInvalidas, int local, int numero);

int defineVazias(TADTabuleiro*, int lin, int col);
void printSugestoes(TADTabuleiro* tabuleiro);

void imprimeTabuleiro(TADTabuleiro *tabuleiro);

#endif //TabuleiroH