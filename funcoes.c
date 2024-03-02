/********************************************************************************
 *  funcoes.c: Criação das funções necessárias para o código.
 *
 *  Autores: Matheus de Andrade Lourenço e Murillo Cardoso Ferreira
 *  Data da Criação: 08/11/2023
 *
 *********************************************************************************/

// Inclusão de bibliotecas e cabeçalhos:

# include <stdio.h>
# include <locale.h>
# include <math.h>
# include <string.h>

# include "funcoes.h"

/********************************************************************************
 *  Função imprimeMatriz: Mostra a matriz no monitor serial
 *
 *  Parâmetros: Quantidade de linhas e colunas da matriz e a matriz.
 *
 *  Retorno: Não há. A função apenas imprime a matriz.
 *
 *********************************************************************************/

void imprimeMatriz(int linhas, int colunas, int matriz[DIM_MAX][DIM_MAX]){

  // Percorrendo a matriz:
  
  for (int i = 0; i < linhas; i++) {
    printf("\n");
    for(int j = 0; j < colunas; j++) {
      // Impressão do elemento:
      
      printf("%d ", matriz[i][j]);
    }
  }
}

/********************************************************************************
 *  Função leMatriz: Mostra a matriz no monitor serial
 *
 *  Parâmetros: Quantidade de linhas e colunas da matriz e a matriz.
 *
 *  Retorno: Não há. A função lê a matriz sem o uso de ponteiros ou alocação
 *  de memória.
 *
 *********************************************************************************/

void leMatriz(int linhas, int colunas, int matriz[DIM_MAX][DIM_MAX]) {
  int valor;  
  for(int i = 0; i < linhas; i++) {
    for(int j = 0; j < colunas; j++) { 
        // Leitura do valor:
        printf("\nDigite o valor da %dª coluna da %dª linha: ", i + 1, j + 1);
        scanf("%d", &valor);
        while(valor != 0 && valor != 1) {
          printf("\nValor inválido, digite novamente: ");
          scanf("%d", &valor);
        }
        // Atribuição do valor lido na matriz:
        matriz[i][j] = valor;
    }
  }
}
/********************************************************************************
 *  Função unico: Verifica se a matriz é homogênea
 *
 *  Parâmetros: Como pode trabalhar com matrizes divididas, os parâmetros são:
 *  início das linhas e das colunas, fim das linhas e das colunas e a matriz.
 *
 *  Retorno: Retorna uma das constantes inteiras, true (1) se for homogênea,
 *  ou false (0), se não for.
 *
 *********************************************************************************/

int unico(int inicioLinhas, int inicioColunas, int fimLinhas, int fimColunas, int matriz[DIM_MAX][DIM_MAX]) {

  // Determinação de um elemento:
  
  int elem = matriz[inicioLinhas][inicioColunas];
  
  for (int i = inicioLinhas; i <= fimLinhas; i++) {
    for(int j = inicioColunas; j <= fimColunas; j++) {
      if(matriz[i][j] != elem) // Comparação do elemento com os demais elementos da matriz.
        return false;
    }
  }
  return true;
}

/********************************************************************************
 *  Função adiciona: Adiciona um caractere a uma string.
 *
 *  Parâmetros: String em que deseja-se realizar a alteração e o caractere a ser
 *  adicionado.
 *
 *  Retorno: Não há, pois a alteração é feita sem alocação de memória ou ponteiros.
 *  
 *********************************************************************************/

void adiciona(char string[], char letra) {
  string[strlen(string)] = letra;
  string[strlen(string) + 1] = '\0';
}

/********************************************************************************
 *  Função analisaQuadrantes: Analisa a matriz com base na função único e gera um 
 *  código para ela, seguindo o algoritmo disponibilizado no descritivo de modo
 *  recursivo.
 *
 *  Parâmetros: Início e fim de linhas e colunas, a matriz, e a string em que será 
 *  armazenada o código.
 *
 *  Retorno: Não há, pois a alteração no código é feita sem alocação de memória ou
 *  ponteiros.
 *
 *********************************************************************************/

void analisaQuadrantes(int matriz[DIM_MAX][DIM_MAX], int inicioLinhas, int inicioColunas, int fimLinhas, int fimColunas, char codigo[]) {

  // Condição que determina um ponto de parada nas divisões:
  if(inicioLinhas > fimLinhas || inicioColunas > fimColunas){return;}
  else 
    // Verifica se a matriz é homogênea:
    
    if (unico(inicioLinhas, inicioColunas, fimLinhas, fimColunas, matriz)){
      int cor = matriz[inicioLinhas][inicioColunas];
      if(cor == 0) adiciona(codigo, 'B'); 
      else if(cor == 1) adiciona(codigo, 'P'); 
      return;
  } else {
      adiciona(codigo, 'X'); // Adiciona X, se não for
  }  

    // Determinação do meio de cada matriz, para facilitar a divisão:
  
    int meioLinhas = (inicioLinhas + fimLinhas) / 2;
    int meioColunas = (inicioColunas + fimColunas) / 2;

    // Chama função para primeiro quadrante

    analisaQuadrantes(matriz, inicioLinhas, inicioColunas, meioLinhas, meioColunas, codigo);

  // Chama função para segundo quadrante

  analisaQuadrantes(matriz, inicioLinhas, meioColunas+1, meioLinhas, fimColunas, codigo);

  // Condição que deve ocorrer para chamada do terceiro quadrante:
  
  if (fimLinhas > 0) {

    // Chama função para terceiro quadrante

    analisaQuadrantes(matriz, meioLinhas+1, inicioColunas, fimLinhas, meioColunas, codigo);

  // Condição que deve ocorrer para chamada do quarto quadrante:
  if (fimColunas > 0) {


    // Chama função para quarto quadrante

     analisaQuadrantes(matriz, meioLinhas+1, meioColunas+1, fimLinhas, fimColunas, codigo);
    }
  }
  
}


