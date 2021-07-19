#define DEBUG 0
#define TAMANHO_TABELA 13

#include <stdio.h>
#include <stdlib.h>

typedef struct elemento* Lista;

typedef struct elemento{
  int dado;
  struct elemento *prox;
}Elemento;

// funções para manipulação da lista
Lista* criar_lista();
int liberar_lista(Lista *li);	
int inserir_lista_final(Lista *li, int dado);
int buscar_lista_dado(Lista *li, int dado, int *pos);
int imprimir_lista(Lista *li);

// funções para manipulação da tabela hash
int chaveDivisao(int chave, int n);
int insereTabelaHash(Lista** tabela, int chave, int n);
int consultaTabelaHash(Lista** tabela, int chave, int n);
int imprimirTabelaHash(Lista** tabela, int n);
void liberaTabelaHash(Lista** tabela);

int main(){

  int opcao, valor, ok;
  Lista *tabela[TAMANHO_TABELA]; 
  
  for(int i = 0; i < TAMANHO_TABELA; i++){
    tabela[i] = criar_lista();
  }

  do {
    if(DEBUG){  
      printf("\n\nMenu de opções");
      printf("\n1 - Inserir valor na tabela hash");
      printf("\n2 - Consultar valor na tabela hash");
      printf("\n3 - Imprimir tabela hash");
      printf("\n9 - Sair");
      printf("\nOpção: ");
    }
    scanf("%d", &opcao);

    switch(opcao){
      case 1: 

        if(DEBUG) printf("\n Valor a ser inserido: ");
        scanf("%d", &valor);      

        ok = insereTabelaHash(tabela, valor, TAMANHO_TABELA);
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

        ok = consultaTabelaHash(tabela, valor, TAMANHO_TABELA);

        if(ok){
          printf("%d\n", valor);
        }else{
          printf("x\n");
        }
        
        break;

      case 3:
        
        ok = imprimirTabelaHash(tabela, TAMANHO_TABELA);
        
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

int chaveDivisao(int chave, int n){
  return (chave & 0x7FFFFFFF) % n;
}

int insereTabelaHash(Lista** tabela, int chave, int n){
  int posicao = chaveDivisao(chave, n);
  int result = inserir_lista_final(tabela[posicao], chave);
  if (DEBUG) printf(" Posição %d", posicao);
  return result;
}

int consultaTabelaHash(Lista** tabela, int chave, int n){
  int posicao = chaveDivisao(chave, n);
  int posicaoLista = 0;
  int result = buscar_lista_dado(tabela[posicao], chave, &posicaoLista);
  return result;
}

int imprimirTabelaHash(Lista** tabela, int n){
  for (int i = 0; i < TAMANHO_TABELA; i++) {
    printf("[%d]: ", i);
    imprimir_lista(tabela[i]);
    printf("\n");
  }
    
  return 1;
}

void liberaTabelaHash(Lista** tabela){
  for(int i = 0; i < TAMANHO_TABELA; i++)
    liberar_lista(tabela[i]);
}

// função para alocar memória do tipo Lista
Lista* criar_lista() {
  Lista *li = (Lista*) malloc(sizeof(Lista));  

  // se a lista foi criada corretamente, indica que ela está vazia
  if(li != NULL){
    *li = NULL;
  } 

  return li;
}


// função para liberar memória
int liberar_lista(Lista *li) {
  if(li == NULL){    
    return 0;
  }

  // libera todos os nós da lista que foram alocados
  Elemento *no;
  while(*li != NULL){
    no = *li;
    *li = (*li)->prox;
    free(no);
  }

  // libera o ponteiro da lista
  free(li);

  return 1;  
}

// função para alocar memória do tipo Elemento
Elemento* criar_elemento() {
  Elemento *no = (Elemento*) malloc(sizeof(Elemento));  

  return no;
}

// função para inserir elemento no final da lista
int inserir_lista_final(Lista *li, int dado) {
  if(li == NULL){
    return 0;
  }

  // cria um elemento novo
  Elemento *no;
  no = criar_elemento();

  if(no == NULL){
    return 0;
  }

  // atribui valores ao elemento novo
  no->dado = dado;
  no->prox = NULL;

  // se a lista estiver vazia, insere no início da lista
  if((*li) == NULL){
    *li = no;
  }else{
    // senão percorre a lista até o fim e insere no final
    Elemento *aux;
    aux = *li;

    while(aux->prox != NULL){
      aux = aux->prox;
    }
    aux->prox = no;
  }

  return 1;
}

int buscar_lista_dado(Lista *li, int dado, int *pos){
  // verifica se a lista foi criada corretamente
  if(li == NULL || (*li) == NULL){
    return 0;
  }

  // procura a posição no vetor onde o dado desejado se encontra
  Elemento *no = *li;
  int i = 1;

  while(no != NULL && no->dado != dado){
    no = no->prox;
    i++;
  }
  
  // verifica se elemento não foi encontrado 
  if(no == NULL){ 
    return 0;
  }

  // copia a posição da lista onde o dado foi encontrado (parâmetro passado por referência)
  *pos = i; 

  return 1;
}

int imprimir_lista(Lista *li){
  if(li == NULL || (*li) == NULL){
    return 0;
  }

  Elemento *aux = (*li);

  while(aux->prox != NULL){
    printf("%d ", aux->dado);
    aux = aux->prox;
  }

  printf("%d ", aux->dado);
    
  return 1;
}