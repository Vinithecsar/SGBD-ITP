#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// O compilador gcc do windows não estava detectando essa função strtok_r,
// então copiei seu código fonte diretamente.
char *strtok_r(char *str, const char *delim, char **save) {
  char *res, *last;

  if (!save)
    return strtok(str, delim);
  if (!str && !(str = *save))
    return NULL;
  last = str + strlen(str);
  if ((*save = res = strtok(str, delim))) {
    *save += strlen(res);
    if (*save < last)
      (*save)++;
    else
      *save = NULL;
  }
  return res;
}

void adicionarLinha() {
  system("clear");
  printf("   |-------------------------------------------------|\n");
  printf("   |              Criar uma nova linha:              |\n");
  printf("   |-------------------------------------------------|\n");

  FILE *arquivoTabela, *arquivoLeitura;
  char nomeTabela[51];

  printf("Digite o nome da tabela: ");
  scanf("%s", nomeTabela);
  strcat(nomeTabela, ".txt");

  // Aqui, há uma checagem para ver se a tabela já existe.
  arquivoLeitura = fopen(nomeTabela, "r");
  if (arquivoLeitura == NULL) {
    printf("Erro ao abrir o arquivo da tabela. Verifique se a tabela existe.\n");
    return;
  }

  arquivoTabela = fopen(nomeTabela, "a+");
  if (arquivoTabela == NULL) {
    printf("Erro ao abrir o arquivo da tabela. Causa: %s\n", strerror(errno));
    return;
  }

  char linhaAAdicionar[151] = "|";
  char linhaColunas[151];
  char linhaTipos[151];
  fgets(linhaColunas, sizeof(linhaColunas), arquivoTabela); // Lê a linha de colunas
  fgets(linhaTipos, sizeof(linhaTipos), arquivoTabela); // Lê a linha de tipos

  char *tokenColuna = NULL, *tokenTipo = NULL;
  char *coluna = NULL, *tipo = NULL;
  coluna = strtok_r(linhaColunas, "|", &tokenColuna);
  tipo = strtok_r(linhaTipos, "|", &tokenTipo);

  int contador = 0;
  int primaryKey;
  while (coluna != NULL) { // Percorre as colunas e tipos da tabela
    char dadoAAdicionar[51];
    if (*coluna != '\n') {
      printf("Qual dado você deseja adicionar na coluna %s - do tipo %s? ", coluna, tipo);
      scanf("%s", dadoAAdicionar);

      if (contador == 0) {
        primaryKey = atoi(dadoAAdicionar);
      }
      strcat(dadoAAdicionar, "|");
      strcat(linhaAAdicionar, dadoAAdicionar);
      contador++;
    }

    coluna = strtok_r(NULL, "|", &tokenColuna);
    tipo = strtok_r(NULL, "|", &tokenTipo);
  }

  fgets(linhaColunas, sizeof(linhaColunas), arquivoLeitura); // Lê a linha de colunas
  fgets(linhaTipos, sizeof(linhaTipos), arquivoLeitura); // Lê a linha de tipos

  char linhaTeste[151];
  while (fgets(linhaTeste, sizeof(linhaTeste), arquivoLeitura)) {
    char *token;
    char *linha = strtok_r(linhaTeste, "|", &token);
    if (atoi(linha) == primaryKey) {
      printf("\nJá existe um elemento com essa chave primária, não é possível adicionar a nova linha.\n\n");
      return;
    }
  }

  rewind(arquivoTabela);
  fprintf(arquivoTabela, "%s\n", linhaAAdicionar);
  fclose(arquivoTabela);
  printf("\nLinha adicionada com sucesso!\n\n");
}

void mostrarDados() {
  // Graças à nossa separação de uma tabela por txt, foi extremamente fácil
  // lidar com a listagem de dados da tabela.
  system("clear");
  printf("   |-------------------------------------------------|\n");
  printf("   |             Listar dados de uma tabela          |\n");
  printf("   |-------------------------------------------------|\n");

  char nomeTabela[51];
  char nomeArquivoTabela[51];
  char linhas[51];
  FILE *arquivoTabela;

  printf("Qual tabela você deseja listar? ");
  scanf("%s", nomeTabela);

  system("clear");

  strcpy(nomeArquivoTabela, nomeTabela);
  strcat(nomeArquivoTabela, ".txt");

  arquivoTabela = fopen(nomeArquivoTabela, "r"); // r -> Abre apenas para a leitura.
  if (arquivoTabela == NULL) {
    printf("Erro ao abrir a tabela. Causa: %s\n", strerror(errno));
    return;
  }

  printf("|-------------------%s---------------------|\n", nomeTabela);
  int contador = 0;
  // Lógica parecida com a listagem de dados de uma tabela. o fscanf em loop
  // para pegar todos os dados da tabela, e logo abaixo, um print.
  while (fscanf(arquivoTabela, "%[^\n]%*[\n]", linhas) == 1) {
    if (contador != 1) {
      printf("               %s                      \n", linhas);
    }
    contador++;
  }
  printf("|------------------------------------------------|\n");
  printf("\n");
}

void apagarLinha() {
  system("clear");
  printf("   |-------------------------------------------------|\n");
  printf("   |             Apagar linha de uma tabela          |\n");
  printf("   |-------------------------------------------------|\n");

  FILE *arquivoTabela, *arquivoAux;
  char nomeTabela[51];

  printf("De qual tabela você deseja apagar a linha? ");
  scanf("%s", nomeTabela);
  strcat(nomeTabela, ".txt");

  arquivoTabela = fopen(nomeTabela, "r");
  if (arquivoTabela == NULL) {
    printf("Erro ao abrir a tabela %s. Causa: %s\n", nomeTabela,
           strerror(errno));
    return;
  }

  arquivoAux = fopen("auxApagarLinha.txt", "w+");
  if (arquivoAux == NULL) {
    printf("Erro ao abrir a tabela auxiliar. Causa: %s\n", strerror(errno));
    fclose(arquivoTabela);
    return;
  }

  char linha[151];
  fgets(linha, sizeof(linha), arquivoTabela);
  fprintf(arquivoAux, "%s", linha);
  char *primaryKeyName = strtok(linha, "|");

  int numLinha;
  printf("Forneça a chave primária %s da linha que deseja apagar: ", primaryKeyName);
  scanf("%d", &numLinha);

  fgets(linha, sizeof(linha), arquivoTabela);
  fprintf(arquivoAux, "%s", linha);

  char linhaOriginal[151];
  int excluiu = 0;
  while (fscanf(arquivoTabela, "%s", linha) != EOF) {
    strcpy(linhaOriginal, linha);
    char *primaryKey = strtok(linha, "|");
    if (atoi(primaryKey) != numLinha) {
      fprintf(arquivoAux, "%s\n", linhaOriginal);
    } else {
      excluiu = 1;
    }
  }

  rewind(arquivoTabela);
  fclose(arquivoTabela);
  remove(nomeTabela);
  fclose(arquivoAux);
  rename("auxApagarLinha.txt", nomeTabela);

  if (excluiu == 0) {
    printf("\nNão foi possível encontrar a linha com a chave primária fornecida!\n\n");
  } else {
    printf("Linha excluída com sucesso!\n");
  }
}

void pesquisarValor() {
  system("clear");
  printf("   |-------------------------------------------------|\n");
  printf("   |           Pesquisar valor em uma tabela         |\n");
  printf("   |-------------------------------------------------|\n");

  FILE *arquivoTabela;
  char nomeTabela[51];

  printf("De qual tabela você deseja realizar a pesquisa? ");
  scanf("%s", nomeTabela);
  strcat(nomeTabela, ".txt");

  arquivoTabela = fopen(nomeTabela, "r");
  if (arquivoTabela == NULL) {
    printf("Erro ao abrir o arquivo da tabela. Verifique se a tabela existe.\n");
    return;
  }

  char linhaColunas[151];
  char linhaTipos[151];
  fgets(linhaColunas, sizeof(linhaColunas),
        arquivoTabela); // Lê a linha de colunas
  fgets(linhaTipos, sizeof(linhaTipos), arquivoTabela); // Lê a linha de tipos

  char *tokenColuna;
  char *tokenTipo;
  char *coluna = strtok_r(linhaColunas, "|", &tokenColuna);
  char *tipo = strtok_r(linhaTipos, "|", &tokenTipo);

  int contador = 0, numColuna;
  printf("Em qual das seguintes colunas você deseja pesquisar?\nEscolha o número correspondente à ela.\n");
  while (coluna != NULL) { // Percorre as colunas e tipos da tabela
    if (*coluna != '\n') {
      contador++;
      printf("%d - Coluna %s - %s\n", contador, coluna, tipo);
    }

    coluna = strtok_r(NULL, "|", &tokenColuna);
    tipo = strtok_r(NULL, "|", &tokenTipo);
  }

  printf("Número escolhido: ");
  scanf("%d", &numColuna);
  if (numColuna < 1 || numColuna > contador) {
    printf("Número fora do intervalo!\n\n");
    fclose(arquivoTabela);
    return;
  }

  rewind(arquivoTabela);
  fgets(linhaColunas, sizeof(linhaColunas), arquivoTabela); // Lê a linha de colunas
  fgets(linhaTipos, sizeof(linhaTipos), arquivoTabela); // Lê a linha de tipos
  coluna = strtok_r(linhaColunas, "|", &tokenColuna);
  tipo = strtok_r(linhaTipos, "|", &tokenTipo);

  char colunaSelecionada[51];
  char tipoSelecionado[51];
  contador = 0;
  while (coluna != NULL) { // Percorre as colunas e tipos da tabela
    if (*coluna != '\n') {
      contador++;
      if (numColuna == contador) {
        strcpy(colunaSelecionada, coluna);
        strcpy(tipoSelecionado, tipo);
        break;
      }
    }

    coluna = strtok_r(NULL, "|", &tokenColuna);
    tipo = strtok_r(NULL, "|", &tokenTipo);
  }

  printf("Coluna selecionada: %s\n", colunaSelecionada);
  printf("Opções de pesquisa:\n");
  printf("1 - Valores maior que o valor informado\n");
  printf("2 - Valores maior ou igual que o valor informado\n");
  printf("3 - Valores igual o valor informado\n");
  printf("4 - Valores menor que o valor informado\n");
  printf("5 - Valores menor ou igual que o valor informado\n");
  if (strcmp(tipoSelecionado, "string") == 0) {
    printf("6 - Valores próximo ao valor informado\n");
  }
  int opcao;
  printf("Opção escolhida: ");
  scanf("%d", &opcao);
  getchar();

  char valorString[51];
  char valorChar;
  float valorIntDoubleOrFloat;
  printf("Digite o valor desejado: ");
  if (strcmp(tipoSelecionado, "string") == 0) {
    scanf("%s", valorString);
  } else if (strcmp(tipoSelecionado, "char") == 0) {
    scanf("%c", &valorChar);
  } else {
    scanf("%fl", &valorIntDoubleOrFloat);
  }

  rewind(arquivoTabela);
  fgets(linhaColunas, sizeof(linhaColunas), arquivoTabela);
  fgets(linhaTipos, sizeof(linhaTipos), arquivoTabela);

  char linhaOriginal[151], linha[151];

  switch (opcao) {

  case (1): {
    while (fscanf(arquivoTabela, "%s", linha) != EOF) {
      strcpy(linhaOriginal, linha);
      char *value = strtok(linha, "|");
      for (int i = 0; i < numColuna - 1; i++) {
        value = strtok(NULL, "|");
      }
      if (strcmp(tipoSelecionado, "string") == 0) {
        if (strcmp(valorString, value) > 0) {
          printf("%s\n", linhaOriginal);
        }
      } else if (strcmp(tipoSelecionado, "char") == 0) {
        if (valorChar > *value) {
          printf("%s\n", linhaOriginal);
        }
      } else {
        if (atof(value) > valorIntDoubleOrFloat) {
          printf("%s\n", linhaOriginal);
        }
      }
    }
    break;
  }
  case (2): {
    while (fscanf(arquivoTabela, "%s", linha) != EOF) {
      strcpy(linhaOriginal, linha);
      char *value = strtok(linha, "|");
      for (int i = 0; i < numColuna - 1; i++) {
        value = strtok(NULL, "|");
      }
      if (strcmp(tipoSelecionado, "string") == 0) {
        if (strcmp(valorString, value) >= 0) {
          printf("%s\n", linhaOriginal);
        }
      } else if (strcmp(tipoSelecionado, "char") == 0) {
        if (valorChar >= *value) {
          printf("%s\n", linhaOriginal);
        }
      } else {
        if (atof(value) >= valorIntDoubleOrFloat) {
          printf("%s\n", linhaOriginal);
        }
      }
    }
    break;
  }
  case (3): {
    while (fscanf(arquivoTabela, "%s", linha) != EOF) {
      strcpy(linhaOriginal, linha);
      char *value = strtok(linha, "|");
      for (int i = 0; i < numColuna - 1; i++) {
        value = strtok(NULL, "|");
      }
      if (strcmp(tipoSelecionado, "string") == 0) {
        if (strcmp(valorString, value) == 0) {
          printf("%s\n", linhaOriginal);
        }
      } else if (strcmp(tipoSelecionado, "char") == 0) {
        if (valorChar == *value) {
          printf("%s\n", linhaOriginal);
        }
      } else {
        if (atof(value) == valorIntDoubleOrFloat) {
          printf("%s\n", linhaOriginal);
        }
      }
    }
    break;
  }
  case (4): {
    while (fscanf(arquivoTabela, "%s", linha) != EOF) {
      strcpy(linhaOriginal, linha);
      char *value = strtok(linha, "|");
      for (int i = 0; i < numColuna - 1; i++) {
        value = strtok(NULL, "|");
      }
      if (strcmp(tipoSelecionado, "string") == 0) {
        if (strcmp(valorString, value) < 0) {
          printf("%s\n", linhaOriginal);
        }
      } else if (strcmp(tipoSelecionado, "char") == 0) {
        if (valorChar < *value) {
          printf("%s\n", linhaOriginal);
        }
      } else {
        if (atof(value) < valorIntDoubleOrFloat) {
          printf("%s\n", linhaOriginal);
        }
      }
    }
    break;
  }
  case (5): {
    while (fscanf(arquivoTabela, "%s", linha) != EOF) {
      strcpy(linhaOriginal, linha);
      char *value = strtok(linha, "|");
      for (int i = 0; i < numColuna - 1; i++) {
        value = strtok(NULL, "|");
      }
      if (strcmp(tipoSelecionado, "string") == 0) {
        if (strcmp(valorString, value) <= 0) {
          printf("%s\n", linhaOriginal);
        }
      } else if (strcmp(tipoSelecionado, "char") == 0) {
        if (valorChar <= *value) {
          printf("%s\n", linhaOriginal);
        }
      } else {
        if (atof(value) <= valorIntDoubleOrFloat) {
          printf("%s\n", linhaOriginal);
        }
      }
    }
    break;
  }
  case (6): {
    if (strcmp(tipoSelecionado, "string") != 0) {
      printf("Operação não permitida!\n\n");
      break;
    }
    while (fscanf(arquivoTabela, "%s", linha) != EOF) {
      strcpy(linhaOriginal, linha);
      char *value = strtok(linha, "|");
      for (int i = 0; i < numColuna - 1; i++) {
        value = strtok(NULL, "|");
      }
      if (strstr(valorString, value)) {
        printf("%s\n", linhaOriginal);
      } else if (strstr(value, valorString)) {
        printf("%s\n", linhaOriginal);
      }
    }
    break;
  }
  default: {
    printf("Opção inválida!\n");
    break;
  }
  }

  fclose(arquivoTabela);
}
