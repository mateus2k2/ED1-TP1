#ifndef TabuleiroH
#define TabuleiroH

typedef struct celula TADCelula;
typedef struct tabuleiro TADTabuleiro;

//Alocacoes e Desalocacoes
void alocaTabuleiro(TADTabuleiro**);
void desalocaTabuleiro(TADTabuleiro**);
void alocaNomeArquivo(char **nomeArquivo, int qtd);
void desalocaNomeArquivo(char **nomeArquivo);
int** alocaMatriz(int lin, int col);
void desalocaMatriz(int **mat, int lin);

//Uso geral
void TabuleiroInicializa(char *nomeArquivo, TADTabuleiro*);
int EhValido(TADTabuleiro* Tabuleiro, int lin, int col, int metodo);

//Printar erros
int ValidaBoard(TADTabuleiro* Tabuleiro);
int** encontraInvalidos(TADTabuleiro* Tabuleiro, int lin, int col, int metodo);
void PrintInvalidas(int** CoordenadasInvalidas, int local, int numero);

//Printar sugestões
int defineVazias(TADTabuleiro*, int lin, int col);
void valoresValidos(TADTabuleiro* tabuleiro);

//Printar o tabuleiro
void imprimeTabuleiro(TADTabuleiro *tabuleiro);

#endif //TabuleiroH