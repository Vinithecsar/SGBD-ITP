#include "operacoesLinha.h"
#include "operacoesTabela.h"
#include <stdio.h>

int main() {
  FILE *arquivoSGBD;
  arquivoSGBD = fopen("sgbd.txt", "a");
  fclose(arquivoSGBD);
  
  printf("    _____ _______ _____     _____  _____ ____  _____  \n");
  printf("   |_   _|__   __|  __ \\   / ____|/ ____|  _ \\|  __ \\ \n");
  printf("     | |    | |  | |__) | | (___ | |  __| |_) | |  | |\n");
  printf("     | |    | |  |  ___/   \\___ \\| | |_ |  _ <| |  | |\n");
  printf("    _| |_   | |  | |       ____) | |__| | |_) | |__| |\n");
  printf("   |_____|  |_|  |_|      |_____/ \\_____|____/|_____/ \n");
  printf("                                                       \n");
  printf("   |-------------------------------------------------|\n");
  printf("   |              Bem vindo ao SGBD ITP!             |\n");
  printf("   | Feito por João Pedro de França e Vinicius César |\n");
  printf("   |                     2023.2                      |\n");
  printf("   |-------------------------------------------------|\n");
  while (1) {
    printf("   |--------------Escolha uma Operação:--------------|\n");
    printf("   |                                                 |\n");
    printf("   |     1º - Criar uma tabela                       |\n");
    printf("   |     2º - Listar todas as tabelas                |\n");
    printf("   |     3º - Criar uma nova linha na tabela         |\n");
    printf("   |     4º - Listar todos os dados de uma tabela    |\n");
    printf("   |     5º - Pesquisar valor em uma tabela          |\n");
    printf("   |     6º - Apagar uma linha de uma tabela         |\n");
    printf("   |     7º - Apagar uma tabela                      |\n");
    printf("   |     8º - Fechar o ITP SGBD                      |\n");
    printf("   |                                                 |\n");
    printf("   |-------------------------------------------------|\n");
    printf("\n");
    printf("\n");

    int operacao;
    printf("    Operação: ");
    scanf("%d", &operacao);

    switch (operacao) {
    case (1):
      criarTabela();
      break;
    case (2):
      listarTabelas();
      break;
    case (3):
      adicionarLinha();
      break;
    case (4):
      mostrarDados();
      break;
    case (5):
      pesquisarValor();
      break;
    case (6):
      apagarLinha();
      break;
    case (7):
      apagarTabela();
      break;
    case (8):
      printf("    Muito obrigado por utilizar o nosso SGBD!\n");
      break;
    }
    if (operacao == 8) {
      break;
    }
  }
  return 0;
}
