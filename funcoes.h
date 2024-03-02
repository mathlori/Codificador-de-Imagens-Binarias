/********************************************************************************
 *  funcoes.h: Determina��o de constantes e armazenamento de cabe�alho de fun��es
 *  para utiliza��o nos arquivos de c�digo.
 *
 *  Autores: Matheus de Andrade Louren�o e Murillo Cardoso Ferreira
 *  Data da Cria��o: 08/11/2023
 *
 *********************************************************************************/

#ifndef _funcoes

# define _funcoes

# define DIM_MAX 100
# define true 1
# define false 0

void imprimeMatriz(int linhas, int colunas, int matriz[DIM_MAX][DIM_MAX]);

void leMatriz(int linhas, int colunas, int matriz[linhas][colunas]);

int teto(float num);

int unico(int inicioLinhas, int inicioColunas, int fimLinhas, int fimColunas, int matriz[DIM_MAX][DIM_MAX]);

void adiciona(char string[], char letra);

void analisaQuadrantes(int matriz[DIM_MAX][DIM_MAX], int inicioLinhas, int inicioColunas, int fimLinhas, int fimColunas, char codigo[]);

# endif
