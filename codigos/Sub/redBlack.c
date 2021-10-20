#define DEBUG 1
#define RED 1
#define BLACK 0

struct NO{
  int info;
  int cor;
  struct NO *esq;
  struct NO *dir;
};

typedef struct NO* ArvRedBlack;

ArvRedBlack* cria_ArvRedBlack();
void libera_NO(struct NO* no);
void libera_ArvRedBlack(ArvRedBlack* raiz);
int corNo_ArvRedBlack(ArvRedBlack *raiz, int valor);
void preOrdem_ArvRedBlack(ArvRedBlack *raiz);
void emOrdem_ArvRedBlack(ArvRedBlack *raiz);
void posOrdem_ArvRedBlack(ArvRedBlack *raiz);
int consulta_ArvRedBlack(ArvRedBlack *raiz, int valor);
int insere(ArvRedBlack *raiz, int valor);
int insere_ArvRedBlack(ArvRedBlack *raiz, int valor);
struct NO* rotateLeft(struct NO *h);
struct NO* rotateRight(struct NO *h);
void flipColors(struct NO  *h); 
int isRed(struct NO  *h);

int main(){

  ArvRedBlack *raiz;
  int opcao, valor, ok;

  raiz = cria_ArvRedBlack();

  if(raiz == NULL){
    printf("\n Árvore não criada!");
    return 0;
  }

  do {
    if(DEBUG){  
      printf("\n\nMenu de opções");
      printf("\n1 - Inserir nó na árvore binária");
      printf("\n2 - Consultar nó na árvore binária");
      printf("\n3 - Percurso pré-ordem");
      printf("\n4 - Percurso em-ordem");
      printf("\n5 - Percurso pós-ordem");
      printf("\n6 - Cor do nó");
      printf("\n7 - Sair");
      printf("\nOpção: ");
    }
    scanf("%d", &opcao);

    switch(opcao){
      case 1: 

        if(DEBUG) printf("\n Valor a ser inserido: ");
        scanf("%d", &valor);      

        ok = insere_ArvRedBlack(raiz, valor);
        if(DEBUG){  
          if(ok == 1){
            printf("\n Inserção realizada com sucesso!");
          }else{
            printf("\n Falha na inserção!");
          }
        }
        break;

      case 2: 
        if(DEBUG) printf("\n Valor a ser buscado: ");
        scanf("%d", &valor); 

        ok = consulta_ArvRedBlack(raiz, valor);

        if(ok == 1)
          printf("%d\n", valor);
        else
          printf("x\n");
        
        break;

      case 3:   
        preOrdem_ArvRedBlack(raiz);
        printf("\n");
        break;

      case 4:   
        emOrdem_ArvRedBlack(raiz);
        printf("\n");
        break;

      case 5:    
        posOrdem_ArvRedBlack(raiz);
        printf("\n");    
        break;

      case 6:
        if(DEBUG) printf("\n Valor a ser buscado: ");
        scanf("%d", &valor); 
        int cor = corNo_ArvRedBlack(raiz, valor);
        if(cor == RED)
          printf("R\n");
        else if (cor == BLACK)
          printf("B\n");
        else
          if(DEBUG) printf("Erro ao buscar a cor\n");
        break;

      case 7:
        libera_ArvRedBlack(raiz);
        break;

      default: 
        if(DEBUG) printf("\nOpção inválida!");
        break;
    }

  }while(opcao != 7);

  return 0;
}

ArvRedBlack* cria_ArvRedBlack(){
  ArvRedBlack* raiz = (ArvRedBlack*) malloc(sizeof(ArvRedBlack));
  if(raiz != NULL)
    *raiz = NULL;
  return raiz;
}

void libera_NO(struct NO* no){
  if(no == NULL)
    return;
  libera_NO(no->esq);
  libera_NO(no->dir);
  free(no);
  no = NULL;
}

void libera_ArvRedBlack(ArvRedBlack* raiz){
  if(raiz == NULL)
    return;
  libera_NO(*raiz);
  free(raiz);
}

int corNo_ArvRedBlack(ArvRedBlack *raiz, int valor){
  if(raiz == NULL)
    return BLACK;
  struct NO* atual = *raiz;
  while(atual != NULL){
    if(valor == atual->info){
      return atual->cor;
    }
    if(valor > atual->info)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
  return -1;
}

void preOrdem_ArvRedBlack(ArvRedBlack *raiz){
  if(raiz == NULL)
    return;
  if(*raiz != NULL){
    printf("%d ",(*raiz)->info);
    preOrdem_ArvRedBlack(&((*raiz)->esq));
    preOrdem_ArvRedBlack(&((*raiz)->dir));
  }
}

void emOrdem_ArvRedBlack(ArvRedBlack *raiz){
  if(raiz == NULL)
    return;
  if(*raiz != NULL){
    emOrdem_ArvRedBlack(&((*raiz)->esq));
    printf("%d ",(*raiz)->info);
    emOrdem_ArvRedBlack(&((*raiz)->dir));
  }
}

void posOrdem_ArvRedBlack(ArvRedBlack *raiz){
  if(raiz == NULL)
    return;
  if(*raiz != NULL){
    posOrdem_ArvRedBlack(&((*raiz)->esq));
    posOrdem_ArvRedBlack(&((*raiz)->dir));
    printf("%d ",(*raiz)->info);
  }
}

int consulta_ArvRedBlack(ArvRedBlack *raiz, int valor){
  if(raiz == NULL)
    return 0;
  struct NO* atual = *raiz;
  while(atual != NULL){
    if(valor == atual->info){
      return 1;
    }
    if(valor > atual->info)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
  return 0;
}

int insere_ArvRedBlack(ArvRedBlack *raiz, int valor){
  int res = 0;
  res = insere(raiz, valor);
  (*raiz)->cor = BLACK;
  return res;
}

int insere(ArvRedBlack *raiz, int valor){
  
  int res = 0;
  if(*raiz == NULL){
    struct NO *novo;
    novo = (struct NO*)malloc(sizeof(struct NO));
    if(novo == NULL)
      return 0;

    novo->info = valor;
    novo->cor = RED;
    novo->esq = NULL;
    novo->dir = NULL;
    *raiz = novo;
    return 1;
  }

  if(valor < (*raiz)->info){
    res = insere(&((*raiz)->esq), valor);
  }else if(valor > (*raiz)->info){
    res = insere(&((*raiz)->dir), valor);
  }else{
    if(DEBUG) printf("Valor duplicado!\n");
    return 0;
  }
  
  if(isRed((*raiz)->dir) && !isRed((*raiz)->esq))
    *raiz = rotateLeft(*raiz);
  if(isRed((*raiz)->esq) && isRed((*raiz)->esq->esq))
    *raiz = rotateRight(*raiz);
  if(isRed((*raiz)->esq) && isRed((*raiz)->dir))
    flipColors(*raiz);
  
  return res;
}

struct NO* rotateLeft(struct NO *h){
  struct NO *x = h->dir;
  h->dir = x->esq;
  x->esq = h;
  x->cor = h->cor;
  h->cor = RED;
  if(DEBUG) printf("Rotate Left \n");
  return x;
}

struct NO* rotateRight(struct NO *h){
  struct NO *x = h->esq;
  h->esq = x->dir;
  x->dir = h;
  x->cor = h->cor;
  h->cor = RED;
  if(DEBUG) printf("Rotate Right \n");
  return x;
}

void flipColors(struct NO  *h) {
  h->cor = RED;
  h->esq->cor = BLACK;
  h->dir->cor = BLACK;
  if(DEBUG) printf("Flip colors \n");
}

int isRed(struct NO  *h){
  if(h == NULL) {
    return 0;
  }
  return h->cor == RED ? 1 : 0;
}