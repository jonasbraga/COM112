// Jonas Henrique Santos Braga
// Giulia Garcia Castro Rodrigues

#define DEBUG 0

#include <stdio.h>
#include <stdlib.h>

struct NO{
  int info;
  int altura;
  struct NO *esq;
  struct NO *dir;
};

typedef struct NO* ArvAVL;

ArvAVL* cria_ArvAVL();
void libera_NO(struct NO* no);
void libera_ArvAVL(ArvAVL* raiz);
int altura_NO(struct NO* no);
int fatorBalanceamento_NO(struct NO* no);
int fatorBalanceamento_valor(ArvAVL *raiz, int valor);
int totalNO_ArvAVL(ArvAVL *raiz);
int altura_ArvAVL(ArvAVL *raiz);
void preOrdem_ArvAVL(ArvAVL *raiz);
void emOrdem_ArvAVL(ArvAVL *raiz);
void posOrdem_ArvAVL(ArvAVL *raiz);
int consulta_ArvAVL(ArvAVL *raiz, int valor);
void RotacaoLL(ArvAVL *A);//L
void RotacaoRR(ArvAVL *A);//R
void RotacaoLR(ArvAVL *A);//L
void RotacaoRL(ArvAVL *A);//R
int insere_ArvAVL(ArvAVL *raiz, int valor);
struct NO* procuraMenor(struct NO* atual);
int remove_ArvAVL(ArvAVL *raiz, int valor);

int main(){

  ArvAVL *raiz;
  int opcao, valor, ok;

  raiz = cria_ArvAVL();

  if(raiz == NULL){
    printf("\n Árvore não criada!");
    return 0;
  }

  do {
    if(DEBUG){  
      printf("\n\nMenu de opções");
      printf("\n1 - Inserir nó na árvore binária");
      printf("\n2 - Consultar nó na árvore binária");
      printf("\n3 - Remover nó da árvore binária");
      printf("\n4 - Percurso pré-ordem");
      printf("\n5 - Percurso em-ordem");
      printf("\n6 - Percurso pós-ordem");
      printf("\n7 - Fator de Balanceamento");
      printf("\n8 - Sair");
      printf("\nOpção: ");
    }
    scanf("%d", &opcao);

    switch(opcao){
      case 1: 

        if(DEBUG) printf("\n Valor a ser inserido: ");
        scanf("%d", &valor);      

        ok = insere_ArvAVL(raiz, valor);
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

        ok = consulta_ArvAVL(raiz, valor);

        if(ok == 1){
          printf("%d\n", valor);
        }else{
          printf("x\n");
        }
        break;

      case 3:
        if(DEBUG) printf("\n Valor a ser removido: ");
        scanf("%d", &valor); 

        ok = remove_ArvAVL(raiz, valor);
        if(DEBUG){ 
          if(ok == 1){
            printf("\n Remoção realizada com sucesso!");
          }else{
            printf("\n Falha na remoção!");
          }
        }
        break;
      case 4:   
        preOrdem_ArvAVL(raiz);
        printf("\n");
        break;

      case 5:   
        emOrdem_ArvAVL(raiz);
        printf("\n");
        break;

      case 6:    
        posOrdem_ArvAVL(raiz);
        printf("\n");    
        break;

      case 7:
        if(DEBUG) printf("\n Valor a ser buscado: ");
        scanf("%d", &valor); 

        printf("%d\n", fatorBalanceamento_valor(raiz, valor));
        break;

      case 8:
        libera_ArvAVL(raiz);
        break;

      default: 
        if(DEBUG) printf("\nOpção inválida!");
        break;
    }

  }while(opcao != 8);

  return 0;
}

ArvAVL* cria_ArvAVL(){
  ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
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

void libera_ArvAVL(ArvAVL* raiz){
  if(raiz == NULL)
    return;
  libera_NO(*raiz);
  free(raiz);
}

int altura_NO(struct NO* no){
  if(no == NULL)
    return -1;
  else
  return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
  return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int fatorBalanceamento_valor(ArvAVL *raiz, int valor){
  if(raiz == NULL)
    return 0;
  struct NO* atual = *raiz;
  while(atual != NULL){
    if(valor == atual->info){
      return altura_NO(atual->dir) - altura_NO(atual->esq);
    }
    if(valor > atual->info)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
  return -2;
}

int maior(int x, int y){
  if(x > y)
    return x;
  else
    return y;
}

int totalNO_ArvAVL(ArvAVL *raiz){
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
  int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
  return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int alt_esq = altura_ArvAVL(&((*raiz)->esq));
  int alt_dir = altura_ArvAVL(&((*raiz)->dir));
  if (alt_esq > alt_dir)
    return (alt_esq + 1);
  else
    return(alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVL *raiz){
  if(raiz == NULL)
    return;
  if(*raiz != NULL){
    printf("%d ",(*raiz)->info);
    preOrdem_ArvAVL(&((*raiz)->esq));
    preOrdem_ArvAVL(&((*raiz)->dir));
  }
}

void emOrdem_ArvAVL(ArvAVL *raiz){
  if(raiz == NULL)
    return;
  if(*raiz != NULL){
    emOrdem_ArvAVL(&((*raiz)->esq));
    printf("%d ",(*raiz)->info);
    emOrdem_ArvAVL(&((*raiz)->dir));
  }
}

void posOrdem_ArvAVL(ArvAVL *raiz){
  if(raiz == NULL)
    return;
  if(*raiz != NULL){
    posOrdem_ArvAVL(&((*raiz)->esq));
    posOrdem_ArvAVL(&((*raiz)->dir));
    printf("%d ",(*raiz)->info);
  }
}

int consulta_ArvAVL(ArvAVL *raiz, int valor){
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

void RotacaoLL(ArvAVL *A){//LL
  if(DEBUG) printf("RotacaoLL\n");
  struct NO *B;
  B = (*A)->esq;
  (*A)->esq = B->dir;
  B->dir = *A;
  (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
  B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
  *A = B;
}

void RotacaoRR(ArvAVL *A){//RR
  if(DEBUG) printf("RotacaoRR\n");
  struct NO *B;
  B = (*A)->dir;
  (*A)->dir = B->esq;
  B->esq = (*A);
  (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
  B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
  (*A) = B;
}

void RotacaoLR(ArvAVL *A){//LR
  RotacaoRR(&(*A)->esq);
  RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){//RL
  RotacaoLL(&(*A)->dir);
  RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, int valor){
  int res;
  if(*raiz == NULL){
    struct NO *novo;
    novo = (struct NO*)malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;

    novo->info = valor;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    *raiz = novo;
    return 1;
  }

  struct NO *atual = *raiz;
  if(valor < atual->info){
    if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){
      if(fatorBalanceamento_NO(atual) >= 2){
        if(valor < (*raiz)->esq->info ){
          RotacaoLL(raiz);
        }else{
          RotacaoLR(raiz);
        }
      }
    }
  }else{
    if(valor > atual->info){
      if((res = insere_ArvAVL(&(atual->dir), valor)) == 1){
        if(fatorBalanceamento_NO(atual) >= 2){
          if((*raiz)->dir->info < valor){
            RotacaoRR(raiz);
          }else{
            RotacaoRL(raiz);
          }
        }
      }
    }else{
      if(DEBUG) printf("Valor duplicado!\n");
      return 0;
    }
  }

  atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

  return res;
}

struct NO* procuraMenor(struct NO* atual){
  struct NO *no1 = atual;
  struct NO *no2 = atual->esq;
  while(no2 != NULL){
    no1 = no2;
    no2 = no2->esq;
  }
  return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){
    if(DEBUG) printf("\n Este valor não existe na árvore!");
    return 0;
	}
  int res;
	if(valor < (*raiz)->info){
    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){
      if(fatorBalanceamento_NO(*raiz) >= 2){
        if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
          RotacaoRR(raiz);
        else
          RotacaoRL(raiz);
      }
    }
	}

	if((*raiz)->info < valor){
    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){
      if(fatorBalanceamento_NO(*raiz) >= 2){
        if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
          RotacaoLL(raiz);
        else
          RotacaoLR(raiz);
      }
    }
	}

	if((*raiz)->info == valor){
    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){
      struct NO *oldNode = (*raiz);
      if((*raiz)->esq != NULL)
        *raiz = (*raiz)->esq;
      else
        *raiz = (*raiz)->dir;
      free(oldNode);
		} else { 
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
      if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
      (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}