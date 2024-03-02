/********************************************************************************
 *  funcoes.c: Cria��o das fun��es necess�rias para o c�digo.
 *
 *  Autores: Matheus de Andrade Louren�o e Murillo Cardoso Ferreira
 *  Data da Cria��o: 08/11/2023
 *
 *********************************************************************************/

// Inclus�o de bibliotecas e cabe�alhos:

# include <stdio.h>
# include <locale.h>
# include <math.h>
# include <string.h>

# include "funcoes.h"

/********************************************************************************
 *  Fun��o imprimeMatriz: Mostra a matriz no monitor serial
 *
 *  Par�metros: Quantidade de linhas e colunas da matriz e a matriz.
 *
 *  Retorno: N�o h�. A fun��o apenas imprime a matriz.
 *
 *********************************************************************************/

void imprimeMatriz(int linhas, int colunas, int matriz[DIM_MAX][DIM_MAX]){

  // Percorrendo a matriz:
  
  for (int i = 0; i < linhas; i++) {
    printf("\n");
    for(int j = 0; j < colunas; j++) {
      // Impress�o do elemento:
      
      printf("%d ", matriz[i][j]);
    }
  }
}

/********************************************************************************
 *  Fun��o leMatriz: Mostra a matriz no monitor serial
 *
 *  Par�metros: Quantidade de linhas e colunas da matriz e a matriz.
 *
 *  Retorno: N�o h�. A fun��o l� a matriz sem o uso de ponteiros ou aloca��o
 *  de mem�ria.
 *
 *********************************************************************************/

void leMatriz(int linhas, int colunas, int matriz[DIM_MAX][DIM_MAX]) {
  int valor;  
  for(int i = 0; i < linhas; i++) {
    for(int j = 0; j < colunas; j++) { 
        // Leitura do valor:
        printf("\nDigite o valor da %d� coluna da %d� linha: ", i + 1, j + 1);
        scanf("%d", &valor);
        while(valor != 0 && valor != 1) {
          printf("\nValor inv�lido, digite novamente: ");
          scanf("%d", &valor);
        }
        // Atribui��o do valor lido na matriz:
        matriz[i][j] = valor;
    }
  }
}
/********************************************************************************
 *  Fun��o unico: Verifica se a matriz � homog�nea
 *
 *  Par�metros: Como pode trabalhar com matrizes divididas, os par�metros s�o:
 *  in�cio das linhas e das colunas, fim das linhas e das colunas e a matriz.
 *
 *  Retorno: Retorna uma das constantes inteiras, true (1) se for homog�nea,
 *  ou false (0), se n�o for.
 *
 *********************************************************************************/

int unico(int inicioLinhas, int inicioColunas, int fimLinhas, int fimColunas, int matriz[DIM_MAX][DIM_MAX]) {

  // Determina��o de um elemento:
  
  int elem = matriz[inicioLinhas][inicioColunas];
  
  for (int i = inicioLinhas; i <= fimLinhas; i++) {
    for(int j = inicioColunas; j <= fimColunas; j++) {
      if(matriz[i][j] != elem) // Compara��o do elemento com os demais elementos da matriz.
        return false;
    }
  }
  return true;
}

/********************************************************************************
 *  Fun��o adiciona: Adiciona um caractere a uma string.
 *
 *  Par�metros: String em que deseja-se realizar a altera��o e o caractere a ser
 *  adicionado.
 *
 *  Retorno: N�o h�, pois a altera��o � feita sem aloca��o de mem�ria ou ponteiros.
 *  
 *********************************************************************************/

void adiciona(char string[], char letra) {
  string[strlen(string)] = letra;
  string[strlen(string) + 1] = '\0';
}

/********************************************************************************
 *  Fun��o analisaQuadrantes: Analisa a matriz com base na fun��o �nico e gera um 
 *  c�digo para ela, seguindo o algoritmo disponibilizado no descritivo de modo
 *  recursivo.
 *
 *  Par�metros: In�cio e fim de linhas e colunas, a matriz, e a string em que ser� 
 *  armazenada o c�digo.
 *
 *  Retorno: N�o h�, pois a altera��o no c�digo � feita sem aloca��o de mem�ria ou
 *  ponteiros.
 *
 *********************************************************************************/

void analisaQuadrantes(int matriz[DIM_MAX][DIM_MAX], int inicioLinhas, int inicioColunas, int fimLinhas, int fimColunas, char codigo[]) {

  // Condi��o que determina um ponto de parada nas divis�es:
  if(inicioLinhas > fimLinhas || inicioColunas > fimColunas){return;}
  else 
    // Verifica se a matriz � homog�nea:
    
    if (unico(inicioLinhas, inicioColunas, fimLinhas, fimColunas, matriz)){
      int cor = matriz[inicioLinhas][inicioColunas];
      if(cor == 0) adiciona(codigo, 'B'); 
      else if(cor == 1) adiciona(codigo, 'P'); 
      return;
  } else {
      adiciona(codigo, 'X'); // Adiciona X, se n�o for
  }  

    // Determina��o do meio de cada matriz, para facilitar a divis�o:
  
    int meioLinhas = (inicioLinhas + fimLinhas) / 2;
    int meioColunas = (inicioColunas + fimColunas) / 2;

    // Chama fun��o para primeiro quadrante

    analisaQuadrantes(matriz, inicioLinhas, inicioColunas, meioLinhas, meioColunas, codigo);

  // Chama fun��o para segundo quadrante

  analisaQuadrantes(matriz, inicioLinhas, meioColunas+1, meioLinhas, fimColunas, codigo);

  // Condi��o que deve ocorrer para chamada do terceiro quadrante:
  
  if (fimLinhas > 0) {

    // Chama fun��o para terceiro quadrante

    analisaQuadrantes(matriz, meioLinhas+1, inicioColunas, fimLinhas, meioColunas, codigo);

  // Condi��o que deve ocorrer para chamada do quarto quadrante:
  if (fimColunas > 0) {


    // Chama fun��o para quarto quadrante

     analisaQuadrantes(matriz, meioLinhas+1, meioColunas+1, fimLinhas, fimColunas, codigo);
    }
  }
  
}


