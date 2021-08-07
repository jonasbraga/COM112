#define DEBUG 0
#define DUMMY "removido"
#define EMPTY "vazio"

#define CHAR_NOME_ALUNO 30
#define CHAR_CURSO 4

const int TAM_BYTES_ALUNO = CHAR_NOME_ALUNO + CHAR_CURSO + 4;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
  char nome[CHAR_NOME_ALUNO];
  char curso[CHAR_CURSO];
  unsigned int matricula;
} Aluno;

typedef struct tableHashAluno{
  char nome[CHAR_NOME_ALUNO];
  int index;
} TableHashAluno;

int quantAlunos = 0;

TableHashAluno* criaTabelaHash(int n);
int chaveDivisao(char *nome, int n);
int chaveString(char *str);
int insereAluno(TableHashAluno* tabela, Aluno aluno, int n, char *nomeArquivo);
int insereTabelaHash(TableHashAluno* tabela, char nome[CHAR_NOME_ALUNO], int n, int *isRemovido, int *fileIndex);
int recuperaArquivoBinario(Aluno *aluno, int fileIndex, char *nomeArquivo);
int insereArquivoBinario(Aluno aluno, char *nomeArquivo, int isRemovido, int fileIndex);
int consultaAluno(TableHashAluno* tabela, char nome[CHAR_NOME_ALUNO], int n, char *nomeArquivo, Aluno *aluno);
int removeTabelaHash(TableHashAluno* tabela, char *nome, int n);
int imprimirTabelaHash(TableHashAluno* tabela, int n, char *nomeArquivo);
void liberaTabelaHash(TableHashAluno* tabela);

int main(){

  int opcao = 0, ok = 0, tamanhoTabela = 0;
  TableHashAluno *tabela;

  char nomeArquivo[500] = {""};
  
  if(DEBUG) printf("Informe o tamanho da tabela: ");
  scanf("%d", &tamanhoTabela);
  
  tabela = criaTabelaHash(tamanhoTabela);

  if(DEBUG) printf("Informe o nome do arquivo: ");
  scanf(" %[^\n]s", nomeArquivo);

  remove(nomeArquivo);

  do {
    if(DEBUG){  
      printf("\n\nMenu de opções");
      printf("\n1 - Inserir novo aluno");
      printf("\n2 - Consultar aluno");
      printf("\n3 - Remover aluno");
      printf("\n4 - Imprimir alunos");
      printf("\n9 - Sair");
      printf("\nOpção: ");
    }
    scanf("%d", &opcao);

    switch(opcao){
      case 1: {

        Aluno aluno; 
        if(DEBUG) printf("\n Nome completo: ");
        scanf(" %[^\n]s", aluno.nome);

        if(DEBUG) printf("\n Sigla do curso: ");
        scanf("%s", aluno.curso);

        if(DEBUG) printf("\n Matricula: ");
        scanf("%u", &aluno.matricula);      

        ok = insereAluno(tabela, aluno, tamanhoTabela, nomeArquivo);
        if(DEBUG){  
          if(ok){
            printf("\n Inserção realizada com sucesso!");
          }else{
            printf("\n Falha na inserção!");
          }
        }
        break;
      }

      case 2: {

        char nome[CHAR_NOME_ALUNO] = {' '};
        if(DEBUG) printf("\n Nome completo: ");
        scanf(" %[^\n]s", nome);
        
        Aluno aluno;
        
        if(!consultaAluno(tabela, nome, tamanhoTabela, nomeArquivo, &aluno)) 
          printf("x\n");
        else
          printf("%d %s %s\n", aluno.matricula, aluno.nome, aluno.curso);

        break;
      }

      case 3:{

        char nome[CHAR_NOME_ALUNO] = {' '};
        if(DEBUG) printf("\n Nome completo: ");
        scanf(" %[^\n]s", nome);
        
        ok = removeTabelaHash(tabela, nome, tamanhoTabela);

        if(DEBUG){ 
          if(ok){
            printf("\n Remoção realizada com sucesso!");
          }else{
            printf("\n Falha na remoção!");
          }
        }
        break;
      }

      case 4:   {
        imprimirTabelaHash(tabela, tamanhoTabela, nomeArquivo);
        printf("\n");
        break;
      }

      case 9:
        liberaTabelaHash(tabela);
        break;

      default: 
        if(DEBUG) printf("\nOpção inválida!");
        break;
    }

  }while(opcao != 9);

  return 0;
}

int insereAluno(TableHashAluno* tabela, Aluno aluno, int n, char *nomeArquivo){
  int isRemovido = 0;
  int fileIndex = 0;
  if(!insereTabelaHash(tabela, aluno.nome, n, &isRemovido, &fileIndex)) return 0;
  if(!insereArquivoBinario(aluno, nomeArquivo, isRemovido, fileIndex)) return 0;

  return 1;
}


TableHashAluno* criaTabelaHash(int n){
  TableHashAluno* tabelaHash = (TableHashAluno*) malloc(n * sizeof(TableHashAluno));
  while(n--) {
    strcpy(tabelaHash[n].nome, EMPTY);
    tabelaHash[n].index = -1;
  }
  return tabelaHash;
}

int chaveDivisao(char *nome, int n){
  return (chaveString(nome) & 0x7FFFFFFF) % n;
}

int chaveString(char *str) {
	int i, valor = 0;
	for (i = 0; i < strlen(str); i++) valor = 31 * valor + (int) str[i];
	return valor;
}

int insereArquivoBinario(Aluno aluno, char *nomeArquivo, int isRemovido, int fileIndex){
  
  FILE *f;
  
  if(isRemovido) {
    f = fopen(nomeArquivo, "rb+");
    if(fseek(f, fileIndex, SEEK_SET)) printf("\n Deu erro seek inserir");
    fwrite(aluno.nome, CHAR_NOME_ALUNO, 1, f);
    if(fseek(f, fileIndex + CHAR_NOME_ALUNO, SEEK_SET)) printf("\n Deu erro seek inserir");
    fwrite(aluno.curso, CHAR_CURSO, 1, f);
    if(fseek(f, fileIndex + CHAR_NOME_ALUNO + CHAR_CURSO, SEEK_SET)) printf("\n Deu erro seek inserir");
    fwrite(&aluno.matricula, sizeof(aluno.matricula), 1, f);
    fclose(f);

  } else {
    f = fopen(nomeArquivo, "a+b");
    quantAlunos++;
    fwrite(aluno.nome, CHAR_NOME_ALUNO, 1, f);
    fwrite(aluno.curso, CHAR_CURSO, 1, f);
    fwrite(&aluno.matricula, sizeof(aluno.matricula), 1, f);
    fclose(f);
  }

  return 1;
}

int recuperaArquivoBinario(Aluno *aluno, int fileIndex, char *nomeArquivo){
  
  FILE *f;
  f = fopen(nomeArquivo, "r+b");
  if(f == NULL) return 0;
  if(fseek(f, fileIndex, SEEK_SET)) printf("\n Deu erro seek consultar");
 
  fread(&aluno->nome, CHAR_NOME_ALUNO, 1, f);
  fread(&aluno->curso, CHAR_CURSO, 1, f);
  fread(&aluno->matricula, sizeof(aluno->matricula), 1, f);

  fclose(f);

  return 1;
}

int insereTabelaHash(TableHashAluno* tabela, char nome[CHAR_NOME_ALUNO], int n, int *isRemovido, int *fileIndex){
  int posicao = chaveDivisao(nome, n);
  while(strcmp(tabela[posicao % n].nome, EMPTY) != 0 && strcmp(tabela[posicao % n].nome, DUMMY) != 0) ++posicao;

  if(strcmp(tabela[posicao % n].nome, DUMMY) == 0){
    *isRemovido = 1;
    *fileIndex = tabela[posicao % n].index;
    strcpy(tabela[posicao % n].nome, nome);
    return 1;
  }

  *fileIndex = quantAlunos * (int)TAM_BYTES_ALUNO;
  tabela[posicao % n].index = *fileIndex;
  strcpy(tabela[posicao % n].nome, nome);
  if (DEBUG) printf(" Inseriu na posicao: %d \n Indice do aquivo: %d \n Nome hash: %s", posicao % n, *fileIndex, tabela[posicao % n].nome);
  return 1;
}

int consultaAluno(TableHashAluno* tabela, char *nome, int n, char *nomeArquivo, Aluno *aluno){
  int posicao = chaveDivisao(nome, n);
  if (DEBUG) printf("\n Posicao consulta: %d\n", posicao);

  while(strcmp(tabela[posicao % n].nome, EMPTY) != 0){
    if(strcmp(tabela[posicao % n].nome, nome) == 0)
      return recuperaArquivoBinario(aluno, tabela[posicao % n].index,nomeArquivo);
        
    posicao++;
  }

  return 0;
}

int removeTabelaHash(TableHashAluno* tabela, char *nome, int n){
  int posicao = chaveDivisao(nome, n);
  if (DEBUG) printf("\n Posicao consulta: %d", posicao);

  for (int i = posicao, contador = 0; (i < n) && contador < n && tabela[i].index != -1; i++, contador++){
    if (strcmp(tabela[i].nome, nome) == 0) strcpy(tabela[i].nome, DUMMY);
    else if (i == n - 1) i = -1;
  }

  return 0;
}

int imprimirTabelaHash(TableHashAluno* tabela, int n, char *nomeArquivo){
  for (int i = 0; i < n; i++){
    //printf("[%d [index: %d, nome: %s]]: ", i, tabela[i].index, tabela[i].nome);
    printf("[%d]: ", i);
    
    if(strcmp(tabela[i].nome, EMPTY) == 0) printf("vazio");
    else if(strcmp(tabela[i].nome, DUMMY) == 0) printf("removido");
    else {
      Aluno aluno;
      recuperaArquivoBinario(&aluno, tabela[i].index, nomeArquivo);
      printf("%d %s %s %d", aluno.matricula, aluno.nome, aluno.curso, tabela[i].index / TAM_BYTES_ALUNO);
    }

    if(i + 1 < n) printf("\n");
  } 
  return 1;
}

void liberaTabelaHash(TableHashAluno* tabela){
  free(tabela);
}