/********************************************************************************
 *  main.c: Cria��o da interface que ser� utilizada na CLI, bem como algoritmo 
 *  para cada op��o selecionada.
 *
 *  Autores: Matheus de Andrade Louren�o e Murillo Cardoso Ferreira
 *  Data da Cria��o: 08/11/2023
 *
 *********************************************************************************/

// Inclus�o de bibliotecas e cabe�alhos:

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#include "funcoes.h"

int main(int argc, char *argv[]) {

    
    int matriz[DIM_MAX][DIM_MAX];
    int linhas;
    int colunas;

    char codigo[DIM_MAX] = "\0";

    setlocale(LC_ALL, "Portuguese");

    if (argc == 2 || argc == 3) {
  
        char opc[3];
        
        strcpy(opc, argv[1]);

        // Codifica��o para a op��o help (-? ou --help)

        if (strcmp(opc, "-?") == 0 || strcmp(opc, "--help") == 0) {

            printf("\nUso: ImageEncoder [-? | -m | -f ARQ]");
            printf("\nCodifica imagens bin�rias com base em informa��es fornecidas em arquivos ou manualmente");
            printf("\nArgumentos: \n");
            printf("\n -?, --help : apresenta essa orienta��o na tela.\n");
            printf("\n-m, --manual: ativa o modo de entrada manual, em que o usu�rio fornece manualmente os dados atrav�s do teclado \n");
            printf("\n-f, --file: Considera a imagem representada no arquivo PBM (portable bitmap)");

        // Codifica��o para a op��o manual (-m ou --manual)
          
        } else if (strcmp(opc, "-m") == 0 || strcmp(opc, "--manual") == 0) {

            // Leitura da matriz:
          
            printf("Digite o n�mero de linhas da matriz: ");
            if (scanf("%d", &linhas) != 1) {
                fprintf(stderr, "Erro ao ler o n�mero de linhas.\n");
                return EXIT_FAILURE;
            }
            while (linhas <= 0) {
                printf("\nValor inv�lido, selecione novamente: ");
                if (scanf("%d", &linhas) != 1) {
                    fprintf(stderr, "Erro ao ler o n�mero de linhas.\n");
                    return EXIT_FAILURE;
                }
            }


            printf("\nDigite o n�mero de colunas da matriz: ");
            if (scanf("%d", &colunas) != 1) {
                fprintf(stderr, "Erro ao ler o n�mero de colunas.\n");
                return EXIT_FAILURE;
            }
            while (colunas <= 0) {
                printf("\nValor inv�lido, selecione novamente: ");
                if (scanf("%d", &colunas) != 1) {
                    fprintf(stderr, "Erro ao ler o n�mero de colunas.\n");
                    return EXIT_FAILURE;
                }
            }
            leMatriz(linhas, colunas, matriz);

            printf("Linhas: %d\nColunas: %d\n", linhas, colunas);

            imprimeMatriz(linhas, colunas, matriz);

            // Execu��o do algoritmo de codifica��o de imagem:

            analisaQuadrantes(matriz, 0, 0, linhas-1, colunas-1, codigo);

            // Sa�da

            printf("\n\nC�digo: %s\n", codigo);

        // Codifica��o para a op��o com leitura de arquivo (-f ou --file):
          
        } else if (strcmp(opc, "-f") == 0 || strcmp(opc, "--file") == 0) {

          //Abertura do arquivo 
          
           FILE *arquivo = fopen(argv[2], "r");

          if (arquivo == NULL) {
              printf("Erro ao abrir o arquivo.\n");
              return 1;
          }
    
          char tipo[DIM_MAX];
  
          if (NULL != fgets(tipo, 3, arquivo) && strcmp(tipo, "P1") != 0) {
            printf("Arquivo PBM inv�lido!");
            return -1;
        }
  
          // Descarte de caracteres n�o num�ricos (tipo do arquivo e coment�rios):
          
          while (fgets(tipo, DIM_MAX, arquivo) != NULL) {
            if(tipo[0] == '#'){ // Caso seja um coment�rio, pular para a pr�xima linha
              fgets(tipo, DIM_MAX, arquivo);
              break;
            }
          }
  
          // Com todos os caracteres n�o num�ricos descartados, realiza-se a leitura das linhas e colunas:
          
          sscanf(tipo, "%d %d", &colunas, &linhas);
  
          printf("Linhas: %d\nColunas: %d\n", linhas, colunas);

          // Leitura dos dados da matriz:
          
          for(int i = 0; i < linhas; i++) {
            for(int j = 0; j < colunas; j++) {
              int valor; 
              fscanf(arquivo, "%d", &valor);
              matriz[i][j] = valor;
            }
            fgets(tipo, DIM_MAX, arquivo);
          }

          // Execu��o do algoritmo de codifica��o de imagem:
          
          printf("\nMatriz: \n");
          imprimeMatriz(linhas, colunas, matriz);
  
          analisaQuadrantes(matriz, 0, 0, linhas, colunas, codigo);
  
          printf("\n\nC�digo: %s\n", codigo);
    }
    }
    return EXIT_SUCCESS;
}
