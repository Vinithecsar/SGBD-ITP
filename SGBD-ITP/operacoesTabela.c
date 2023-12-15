#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criarTabela() {
  char nome[51];
  int numColunas;
  FILE *arquivoSGBD;
  FILE *arquivoTabela;
  FILE *jaExiste;

  arquivoSGBD = fopen("sgbd.txt", "a+");
  // a+ -> Abre para a escrita. Se diferencia do W,
  // pois com o a, o programa checa se o arquivo já
  // existe, apenas adicionando as tabelas.

  if (arquivoSGBD == NULL) { // Se não existir o sgbd.txt
    arquivoSGBD = fopen("sgbd.txt", "a");
    if (arquivoSGBD == NULL) {
      printf("Erro ao abrir o sgbd. Causa: %s\n", strerror(errno));
      // O errno nos dá a mensagem de erro exata do problema.
    }
  }

  system("clear");
  printf("|-------------------------------------------------|\n");
  printf("|              Criação de Tabela.                 |\n");
  printf("|-------------------------------------------------|\n");

  printf("\nDigite o nome da sua tabela: ");
  scanf("%s", nome);
  printf("\nQuantas colunas a sua tabela terá? ");
  scanf("%d", &numColunas);
  strcat(nome, ".txt");

  fprintf(arquivoSGBD, "%s\n", nome);

  jaExiste = fopen(nome, "r");
  if (jaExiste != NULL) {
    printf("A tabela já existe!\n");
    return;
  }

  // Criação do arquivo que guarda a tabela
  arquivoTabela = fopen(nome, "w+");

  char tiposString[151] = "|";
  for (int i = 0; i < numColunas + 1; i++) {
    int tipoEntrada;

    char tipo[51];
    char nomeColuna[51];

    // Lógica do identificador (Chave primária)
    if (i == 0) {
      printf("|-------------------------------------------------|\n");
      printf("|       Insira o nome da chave primária           |\n");
      printf("|-------------------------------------------------|\n");
      strcpy(tipo, "int|");
      strcat(tiposString, tipo);
      printf("Digite o nome da chave primária: ");
      scanf(" %s", nomeColuna);
      fprintf(arquivoTabela, "|%s|", nomeColuna);
    } else {
      // Lógica da entrada de dados usando apenas os tipos citados no arquivo
      // que explica o trabalho
      system("clear");
      printf("|------------Tipo de dado da %dª coluna---------|\n", i + 1);
      printf("|                 1 - int                      |\n");
      printf("|                 2 - char                     |\n");
      printf("|                 3 - float                    |\n");
      printf("|                 4 - double                   |\n");
      printf("|                 5 - string                   |\n");
      printf("|----------------------------------------------|\n");

      printf("Qual será o tipo da coluna? (Insira o número): ");
      scanf("%d", &tipoEntrada);

      switch (tipoEntrada) {
      case 1:
        strcpy(tipo, "int|");
        break;
      case 2:
        strcpy(tipo, "char|");
        break;
      case 3:
        strcpy(tipo, "float|");
        break;
      case 4:
        strcpy(tipo, "double|");
        break;
      case 5:
        strcpy(tipo, "string|");
        break;
      default:
        printf("Opção inválida!\n");
        break;
      }
      strcat(tiposString, tipo);
      printf("\nQual será o nome da coluna? ");
      scanf("%s", nomeColuna);

      fprintf(arquivoTabela, "%s|", nomeColuna);
    }
  }

  fprintf(arquivoTabela, "\n");
  fprintf(arquivoTabela, "%s\n", tiposString);
  fclose(arquivoTabela);
  fclose(arquivoSGBD);
  system("clear");

  // Usamos os "clear" para limpar o console.
}

void listarTabelas() {
  // Graças ao nosso arquivo sgbd.txt, a listagem de tabelas foi muito
  // facilitada

  system("clear");
  printf("   |-------------------------------------------------|\n");
  printf("   |              Listagem de tabelas:               |\n");
  printf("   |-------------------------------------------------|\n");

  FILE *arquivoSGBD;
  char tabelas[51];
  char continuar;

  arquivoSGBD = fopen("sgbd.txt", "r"); // r -> Abre apenas para a leitura.
  if (arquivoSGBD == NULL) {            // Se não existir o sgbd.txt
    printf("Erro ao abrir o sgbd. Causa: %s\n", strerror(errno));
    return;
  }

  while (fscanf(arquivoSGBD, "%[^\n]%*[\n]", tabelas) == 1) {
    // o "%[^\n]%*[\n]" lê uma linha inteira de um arquivo, exclui o
    // caractere de nova linha, e avança para a próxima linha.
    char *ponto = strrchr(tabelas, '.');
    size_t comprimentoSemExtensao = ponto - tabelas;
    tabelas[comprimentoSemExtensao] = '\0';
    printf("                        %s                      \n", tabelas);
  }
  printf("   |-------------------------------------------------|\n");

  fclose(arquivoSGBD);
  printf("\n\n");
}

void apagarTabela() {
  system("clear");
  printf("   |-------------------------------------------------|\n");
  printf("   |                Deletar uma tabela:              |\n");
  printf("   |-------------------------------------------------|\n");

  char continuar;
  printf("Para deletar uma tabela, é necessário informar o nome dela (CASE SENSITIVE!)\n");
  printf("Você precisa de uma listagem de tabelas antes de continuar? (S/N) ");
  scanf(" %c", &continuar);

  if (continuar == 'S' || continuar == 's') {
    listarTabelas();
  }

  char nomeTabela[51];
  char nomeTemp[51];

  printf("Qual tabela você deseja deletar? ");
  scanf("%s", nomeTabela);
  strcat(nomeTabela, ".txt");

  FILE *arquivoTabela = fopen(nomeTabela, "r");
  if (arquivoTabela == NULL) {
    printf("Erro ao abrir o arquivo da tabela. Causa: %s\n", strerror(errno));
    return;
  }
  fclose(arquivoTabela);
  // Aqui há a remoção do arquivo txt da tabela.
  remove(nomeTabela);

  FILE *arquivoSGBD = fopen("sgbd.txt", "r+");
  if (arquivoSGBD == NULL) {
    printf("Erro ao abrir o SGBD. Causa: %s\n", strerror(errno));
    return;
  }

  FILE *arquivoTemp = fopen("temp.txt", "w");
  if (arquivoTemp == NULL) {
    printf("Erro ao abrir o novo arquivo.\n");
    fclose(arquivoSGBD);
    return;
  }

  // Lê linha por linha do arquivo SGBD e escreve linha por linha no
  // arquivo temporário, exceto a linha que contém a tabela a ser deletada
  while (fscanf(arquivoSGBD, "%s", nomeTemp) != EOF) {
    if (strcmp(nomeTemp, nomeTabela) != 0) {
      fprintf(arquivoTemp, "%s\n", nomeTemp);
    }
  }

  fclose(arquivoSGBD);
  remove("sgbd.txt");
  printf("Tabela deletada com sucesso!\n");
  fclose(arquivoTemp);
  rename("temp.txt", "sgbd.txt");
}