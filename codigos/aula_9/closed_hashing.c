#define DEBUG 0
#define DUMMY 68857789
#define EMPTY 69778089

#include <stdio.h>
#include <stdlib.h>

int* criaTabelaHash(int n);
int chaveDivisao(int chave, int n);
int insereTabelaHash(int* tabela, int chave, int n);
int consultaTabelaHash(int* tabela, int chave, int n);
int removeTabelaHash(int* tabela, int posicao, int n);
int imprimirTabelaHash(int* tabela, int n);
void liberaTabelaHash(int* tabela);

int main(){

  int opcao, valor, ok, tamanhoTabela, *tabela;
  
  if(DEBUG) printf("Informe o tamanho da tabela: ");
  scanf("%d", &tamanhoTabela);
  
  tabela = criaTabelaHash(tamanhoTabela);

  do {
    if(DEBUG){  
      printf("\n\nMenu de opções");
      printf("\n1 - Inserir valor na tabela hash");
      printf("\n2 - Consultar valor na tabela hash");
      printf("\n3 - Remover valor da tabela hash");
      printf("\n4 - Imprimir tabela hash");
      printf("\n9 - Sair");
      printf("\nOpção: ");
    }
    scanf("%d", &opcao);

    switch(opcao){
      case 1: 

        if(DEBUG) printf("\n Valor a ser inserido: ");
        scanf("%d", &valor);      

        ok = insereTabelaHash(tabela, valor, tamanhoTabela);
        if(DEBUG){  
          if(ok){
            printf("\n Inserção realizada com sucesso!");
          }else{
            printf("\n Falha na inserção!");
          }
        }
        break;

      case 2: 
        if(DEBUG) printf("\n Valor a ser buscado: ");
        scanf("%d", &valor); 

        ok = consultaTabelaHash(tabela, valor, tamanhoTabela);

        printf("%d\n", ok);
        
        break;

      case 3:
        if(DEBUG) printf("\n Valor a ser removido: ");
        scanf("%d", &valor); 

        ok = removeTabelaHash(tabela, valor, tamanhoTabela);
        if(DEBUG){ 
          if(ok){
            printf("\n Remoção realizada com sucesso!");
          }else{
            printf("\n Falha na remoção!");
          }
        }
        break;
      case 4:   
        imprimirTabelaHash(tabela, tamanhoTabela);
        printf("\n");
        break;

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

int* criaTabelaHash(int n){
  int* tabelaHash = (int*) malloc(n * sizeof(int));
  while(n--) tabelaHash[n] = EMPTY;
  return tabelaHash;
}

int chaveDivisao(int chave, int n){
  return (chave & 0x7FFFFFFF) % n;
}

int insereTabelaHash(int* tabela, int chave, int n){
  int posicao = chaveDivisao(chave, n);
  while(tabela[posicao % n] != EMPTY && tabela[posicao % n] != DUMMY) ++posicao;
  tabela[posicao % n] = chave;
  if (DEBUG) printf(" Inseriu na posicao %d", posicao % n);
  return 1;
}

int consultaTabelaHash(int* tabela, int chave, int n){
  int posicao = chaveDivisao(chave, n);
  while(tabela[posicao % n] != EMPTY && tabela[posicao % n] != chave) ++posicao;
  return tabela[posicao % n] == chave ? posicao % n : -1;
}

int removeTabelaHash(int* tabela, int posicao, int n){
  
  tabela[posicao] = DUMMY;
  return 1;
}

int imprimirTabelaHash(int* tabela, int n){
  for (int i = 0; i < n; i++) 
    if(tabela[i] != EMPTY && tabela[i] != DUMMY) printf("%d ", tabela[i]);
  return 1;
}

void liberaTabelaHash(int* tabela){
  free(tabela);
}