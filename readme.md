## Projeto feito por João Pedro de França e Vinicius César.

## O que cada um fez?
> Primeiro, é bom pontuar, que ninguém fez nenhuma ação 100% sozinho.<br/>
> A construção das ideias foi em conjunto, buscando a maior praticidade.

> **Menu principal:** João Pedro e Vinícius<br/>
> **Criar Tabela:** João Pedro<br/>
> **Listar Tabelas:** João Pedro<br/>
> **Criar Linha na Tabela:** Vinícius<br/>
> **Listar todos os dados de uma tabela:** João Pedro<br/>
> **Pesquisar valor em uma tabela:** Vinícius<br/>
> **Apagar uma linha na tabela:** Vinícius<br/>
> **Apagar uma tabela:** João Pedro e Vinícius<br/>
> **Documentação:** João Pedro e Vinícius<br/>


## O que deixou de ser feito/usado

> O que deixou de ser feito? <br/>
 > Nada! Os requisitos básicos foram feitos com sucesso!

> O que deixou de ser usado? <br/>
 > Não vimos o uso de structs como proveitoso no projeto. A dinâmica com os txts pareceu mais eficiente para o curto prazo.

> O que nos arrependemos de não ter feito: <br/>
> Talvez o uso de funções que encurtassem certas ações fosse bem proveitoso, como por exemplo, uma função para abrir um arquivo de determinada maneira.


## Comentários e análises interessantes:

> Optamos por fazer um txt chamado "SGBD" que guardasse apenas os nomes das tabelas, o qual é criado automaticamente na primeira execução do programa.
 > Isso facilitou muito para fazer a listagem de tabelas.


> Optamos por fazer cada tabela num arquivo diferente, com o arquivo tendo o nome da tabela.<br/>
 > Isso facilitou muito a listagem dos dados da tabela.

## Como compilar o projeto:

> Pré-requisito: Ter o compilar GCC instalado no computador<br/>
> Passo a passo:
> 1. Abrir o terminal de comando de sua escolha (Ex.: cmd ou PowerShell)
> 2. Abrir a pasta que se encontram os arquivos do projeto (no cmd, utilizar "dir" e no PowerShell e terminais linux utilizar "cd")
> 3. Digitar o comando ```gcc main.c operacoesLinha.c operacoesTabela.c -o bancoITP -g -W``` e esperar o compilador gerar o executável do programa
> 4. Digitar o comando ```bancoItp.exe``` e esperar o programa inicializar

## Documentação:

### main.c
> Está definida a função main, que é responsável por inicializar o programa, assim como redirecionar para cada umas das funções do sistema.
>
### operacoesLinha.c
> Estão definidas as funções do sistema relacionadas com operações de linhas.
>
>  **adicionarLinha**: Pergunta-se o nome da tabela a ser adicionada a linha, e qual dado deseja ser inserido em cada uma das tabelas.<br/><br/>
>  **mostrarDados**: Pergunta-se o nome da tabela na qual deseja-se listar os dados, e então os lista.<br/><br/>
>  **apagarLinha**: Pergunta-se o nome da tabela na qual deseja-se apagar uma linha, qual a chave primária da linha que deseja apagar, e então a apaga.<br/><br/>
>  **pesquisarValor**: Pergunta-se o nome da tabela na qual deseja-se pesquisar valores, lista as colunas e pede para o usuário escolher uma delas de acordo com um número, são oferecidas 5 opções de pesquisa, sendo elas<br/>
> "valores maior que o valor informado",<br/>
> "valores maior ou igual que o valor informado",<br/>
> "valores igual o valor informado",<br/>
> "valores menor que o valor informado" ou<br/>
> "valores menor ou igual que o valor informado".<br/>
> Caso seja uma string, também será oferecida a opção "valores próximo ao valor informado".<br/>
> Então, é pergutado o valor que deseja ser pesquisado e são mostradas as linhas resultantes.<br/>
### operacoesLinha.h
> Estão declaradas as funções definidas em operacoesLinha.c, a fim de poderem ser utilizadas em outros arquivos por meio do "include".
### operacoesTabela.c
> Estão definidas as funções do sistema relacionadas com operações de linhas.
>
>  **criarTabela**: Pergunta-se o nome da tabela a ser criada, quantas colunas a tabela terá, o nome da chave primária, e então o tipo e os nomes das outras colunas.<br/><br/>
>  **listarTabela**: As tabelas são listadas.<br/><br/>
>  **apagarTabela**: É perguntado se o usuário deseja ter uma listagem das tabelas antes de continuar, pergunta qual tabela deseja excluir, e, caso exista, é então excluída.<br/>
### operacoesTabela.h
> Estão declaradas as funções definidas em operacoesTabela.c, a fim de poderem ser utilizadas em outros arquivos por meio do "include".
