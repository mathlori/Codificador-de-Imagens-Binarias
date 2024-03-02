/********************************************************************************
 *  main.c: Criação da interface que será utilizada na CLI, bem como algoritmo 
 *  para cada opção selecionada.
 *
 *  Autores: Matheus de Andrade Lourenço e Murillo Cardoso Ferreira
 *  Data da Criação: 08/11/2023
 *
 *********************************************************************************/

// Inclusão de bibliotecas e cabeçalhos:

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

        // Codificação para a opção help (-? ou --help)

        if (strcmp(opc, "-?") == 0 || strcmp(opc, "--help") == 0) {

            printf("\nUso: ImageEncoder [-? | -m | -f ARQ]");
            printf("\nCodifica imagens binárias com base em informações fornecidas em arquivos ou manualmente");
            printf("\nArgumentos: \n");
            printf("\n -?, --help : apresenta essa orientação na tela.\n");
            printf("\n-m, --manual: ativa o modo de entrada manual, em que o usuário fornece manualmente os dados através do teclado \n");
            printf("\n-f, --file: Considera a imagem representada no arquivo PBM (portable bitmap)");

        // Codificação para a opção manual (-m ou --manual)
          
        } else if (strcmp(opc, "-m") == 0 || strcmp(opc, "--manual") == 0) {

            // Leitura da matriz:
          
            printf("Digite o número de linhas da matriz: ");
            if (scanf("%d", &linhas) != 1) {
                fprintf(stderr, "Erro ao ler o número de linhas.\n");
                return EXIT_FAILURE;
            }
            while (linhas <= 0) {
                printf("\nValor inválido, selecione novamente: ");
                if (scanf("%d", &linhas) != 1) {
                    fprintf(stderr, "Erro ao ler o número de linhas.\n");
                    return EXIT_FAILURE;
                }
            }


            printf("\nDigite o número de colunas da matriz: ");
            if (scanf("%d", &colunas) != 1) {
                fprintf(stderr, "Erro ao ler o número de colunas.\n");
                return EXIT_FAILURE;
            }
            while (colunas <= 0) {
                printf("\nValor inválido, selecione novamente: ");
                if (scanf("%d", &colunas) != 1) {
                    fprintf(stderr, "Erro ao ler o número de colunas.\n");
                    return EXIT_FAILURE;
                }
            }
            leMatriz(linhas, colunas, matriz);

            printf("Linhas: %d\nColunas: %d\n", linhas, colunas);

            imprimeMatriz(linhas, colunas, matriz);

            // Execução do algoritmo de codificação de imagem:

            analisaQuadrantes(matriz, 0, 0, linhas-1, colunas-1, codigo);

            // Saída

            printf("\n\nCódigo: %s\n", codigo);

        // Codificação para a opção com leitura de arquivo (-f ou --file):
          
        } else if (strcmp(opc, "-f") == 0 || strcmp(opc, "--file") == 0) {

          //Abertura do arquivo 
          
           FILE *arquivo = fopen(argv[2], "r");

          if (arquivo == NULL) {
              printf("Erro ao abrir o arquivo.\n");
              return 1;
          }
    
          char tipo[DIM_MAX];
  
          if (NULL != fgets(tipo, 3, arquivo) && strcmp(tipo, "P1") != 0) {
            printf("Arquivo PBM inválido!");
            return -1;
        }
  
          // Descarte de caracteres não numéricos (tipo do arquivo e comentários):
          
          while (fgets(tipo, DIM_MAX, arquivo) != NULL) {
            if(tipo[0] == '#'){ // Caso seja um comentário, pular para a próxima linha
              fgets(tipo, DIM_MAX, arquivo);
              break;
            }
          }
  
          // Com todos os caracteres não numéricos descartados, realiza-se a leitura das linhas e colunas:
          
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

          // Execução do algoritmo de codificação de imagem:
          
          printf("\nMatriz: \n");
          imprimeMatriz(linhas, colunas, matriz);
  
          analisaQuadrantes(matriz, 0, 0, linhas, colunas, codigo);
  
          printf("\n\nCódigo: %s\n", codigo);
    }
    }
    return EXIT_SUCCESS;
}
