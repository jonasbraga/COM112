#define DEBUG 0
#define RED 1
#define BLACK 0

#include <stdio.h>
#include <stdlib.h>

int tamanhoTabelaGlobal = 0;

struct NO
{
  int info;
  int cor;
  int altura;
  struct NO *esq;
  struct NO *dir;
};

typedef struct NO *ArvAVLRedBlack;

// Tabela hash
ArvAVLRedBlack **criaTabelaHash(int n);
int chaveDivisao(int chave, int n);
int insereTabelaHash(ArvAVLRedBlack **tabela, int chave, int n);
int consultaTabelaHash(ArvAVLRedBlack **tabela, int chave, int n);
int removeTabelaHash(ArvAVLRedBlack **tabela, int chave, int n);
int imprimirTabelaHash(ArvAVLRedBlack **tabela, int n);
void liberaTabelaHash(ArvAVLRedBlack **tabela);

// Comum
ArvAVLRedBlack *cria_ArvAVLRedBlack();
void libera_NO(struct NO *no);
void libera_ArvAVLRedBlack(ArvAVLRedBlack *raiz);

// AVL
int altura_NO(struct NO *no);
int fatorBalanceamento_NO(struct NO *no);
int fatorBalanceamento_valor(ArvAVLRedBlack *raiz, int valor);
int totalNO_ArvAVL(ArvAVLRedBlack *raiz);
int altura_ArvAVL(ArvAVLRedBlack *raiz);
void preOrdem_ArvAVL(ArvAVLRedBlack *raiz);
void emOrdem_ArvAVL(ArvAVLRedBlack *raiz);
void posOrdem_ArvAVL(ArvAVLRedBlack *raiz);
int consulta_ArvAVL(ArvAVLRedBlack *raiz, int valor);
void RotacaoLL(ArvAVLRedBlack *A); //L
void RotacaoRR(ArvAVLRedBlack *A); //R
void RotacaoLR(ArvAVLRedBlack *A); //L
void RotacaoRL(ArvAVLRedBlack *A); //R
int insere_ArvAVL(ArvAVLRedBlack *raiz, int valor);
struct NO *procuraMenor(struct NO *atual);
int remove_ArvAVL(ArvAVLRedBlack *raiz, int valor);

// RedBlack
int corNo_ArvRedBlack(ArvAVLRedBlack *raiz, int valor);
void preOrdem_ArvRedBlack(ArvAVLRedBlack *raiz);
void emOrdem_ArvRedBlack(ArvAVLRedBlack *raiz);
void posOrdem_ArvRedBlack(ArvAVLRedBlack *raiz);
int consulta_ArvRedBlack(ArvAVLRedBlack *raiz, int valor);
int insere(ArvAVLRedBlack *raiz, int valor);
int insere_ArvRedBlack(ArvAVLRedBlack *raiz, int valor);
struct NO *rotateLeft(struct NO *h);
struct NO *rotateRight(struct NO *h);
int remove_ArvRedBlack(ArvAVLRedBlack *raiz, int valor);
void flipColors(struct NO *h);
int isRed(struct NO *h);

int main()
{

  int opcao, valor, ok, tamanhoTabela;

  ArvAVLRedBlack **tabela;

  if (DEBUG)
    printf("Informe o tamanho da tabela: ");
  scanf("%d", &tamanhoTabela);

  tabela = criaTabelaHash(tamanhoTabela);
  tamanhoTabelaGlobal = tamanhoTabela;
  do
  {
    if (DEBUG)
    {
      printf("\n\nMenu de opções");
      printf("\n1 - Inserir valor na tabela hash");
      printf("\n2 - Consultar valor na tabela hash");
      printf("\n3 - Remover valor tabela hash");
      printf("\n4 - Imprimir tabela hash");
      printf("\n9 - Sair");
      printf("\nOpção: ");
    }
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:

      if (DEBUG)
        printf("\n Valor a ser inserido: ");
      scanf("%d", &valor);

      ok = insereTabelaHash(tabela, valor, tamanhoTabelaGlobal);
      if (DEBUG)
      {
        if (ok)
        {
          printf("\n Inserção realizada com sucesso!");
        }
        else
        {
          printf("\n Falha na inserção!");
        }
      }
      break;

    case 2:
      if (DEBUG)
        printf("\n Valor a ser buscado: ");
      scanf("%d", &valor);

      ok = consultaTabelaHash(tabela, valor, tamanhoTabelaGlobal);

      if (ok)
      {
        printf("%d\n", valor);
      }
      else
      {
        printf("x\n");
      }

      break;

    case 3:
      if (DEBUG)
        printf("\n Valor a ser removido: ");
      scanf("%d", &valor);

      ok = removeTabelaHash(tabela, valor, tamanhoTabelaGlobal);

      if (DEBUG)
      {
        if (ok)
        {
          printf("Removido \n");
        }
        else
        {
          printf("Não removido\n");
        }
      }

      break;

    case 4:
      ok = imprimirTabelaHash(tabela, tamanhoTabelaGlobal);

      break;

    case 9:
      liberaTabelaHash(tabela);
      break;

    default:
      if (DEBUG)
        printf("\nOpção inválida!");
      break;
    }

  } while (opcao != 9);

  return 0;
}

// Tabela Hash
ArvAVLRedBlack **criaTabelaHash(int n)
{
  ArvAVLRedBlack **tabelaHash = (ArvAVLRedBlack **)malloc(n * sizeof(ArvAVLRedBlack));
  for (int i = 0; i < n; i++)
  {
    tabelaHash[i] = cria_ArvAVLRedBlack();
  }
  return tabelaHash;
}

int chaveDivisao(int chave, int n)
{
  return (chave & 0x7FFFFFFF) % n;
}

int insereTabelaHash(ArvAVLRedBlack **tabela, int chave, int n)
{
  int posicao = chaveDivisao(chave, n);

  if (DEBUG)
    printf(" Posição %d", posicao);

  int result = posicao % 2 ? insere_ArvRedBlack(tabela[posicao], chave) : insere_ArvAVL(tabela[posicao], chave);

  return result;
}

int consultaTabelaHash(ArvAVLRedBlack **tabela, int chave, int n)
{
  int posicao = chaveDivisao(chave, n);

  if (DEBUG)
    printf(" Posição %d", posicao);

  int result = posicao % 2 ? consulta_ArvRedBlack(tabela[posicao], chave) : consulta_ArvAVL(tabela[posicao], chave);

  return result;
}

int removeTabelaHash(ArvAVLRedBlack **tabela, int chave, int n)
{
  int posicao = chaveDivisao(chave, n);

  if (DEBUG)
    printf(" Posição %d", posicao);

  int result = posicao % 2 ? remove_ArvRedBlack(tabela[posicao], chave) : remove_ArvAVL(tabela[posicao], chave);
  //int result = remove_ArvAVL(tabela[posicao], chave);

  return result;
}

int imprimirTabelaHash(ArvAVLRedBlack **tabela, int n)
{
  for (int i = 0; i < tamanhoTabelaGlobal; i++)
  {
    printf("[%d]: ", i);
    if (i % 2)
      preOrdem_ArvRedBlack(tabela[i]);
    else
      preOrdem_ArvAVL(tabela[i]);

    printf("\n");
  }

  return 1;
}

void liberaTabelaHash(ArvAVLRedBlack **tabela)
{
  for (int i = 0; i < tamanhoTabelaGlobal; i++)
    libera_ArvAVLRedBlack(tabela[i]);
}

// Comum
ArvAVLRedBlack *cria_ArvAVLRedBlack()
{
  ArvAVLRedBlack *raiz = (ArvAVLRedBlack *)malloc(sizeof(ArvAVLRedBlack));
  if (raiz != NULL)
    *raiz = NULL;
  return raiz;
}

void libera_NO(struct NO *no)
{
  if (no == NULL)
    return;
  libera_NO(no->esq);
  libera_NO(no->dir);
  free(no);
  no = NULL;
}

void libera_ArvAVLRedBlack(ArvAVLRedBlack *raiz)
{
  if (raiz == NULL)
    return;
  libera_NO(*raiz);
  free(raiz);
}

// AVL
int altura_NO(struct NO *no)
{
  if (no == NULL)
    return -1;
  else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO *no)
{
  return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int fatorBalanceamento_valor(ArvAVLRedBlack *raiz, int valor)
{
  if (raiz == NULL)
    return 0;
  struct NO *atual = *raiz;
  while (atual != NULL)
  {
    if (valor == atual->info)
    {
      return altura_NO(atual->dir) - altura_NO(atual->esq);
    }
    if (valor > atual->info)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
  return -2;
}

int maior(int x, int y)
{
  if (x > y)
    return x;
  else
    return y;
}

int totalNO_ArvAVL(ArvAVLRedBlack *raiz)
{
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
  int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
  return (alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVLRedBlack *raiz)
{
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int alt_esq = altura_ArvAVL(&((*raiz)->esq));
  int alt_dir = altura_ArvAVL(&((*raiz)->dir));
  if (alt_esq > alt_dir)
    return (alt_esq + 1);
  else
    return (alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVLRedBlack *raiz)
{
  if (raiz == NULL)
    return;
  if (*raiz != NULL)
  {
    printf("%d(%d) ", (*raiz)->info, fatorBalanceamento_NO(*raiz));
    preOrdem_ArvAVL(&((*raiz)->esq));
    preOrdem_ArvAVL(&((*raiz)->dir));
  }
}

void emOrdem_ArvAVL(ArvAVLRedBlack *raiz)
{
  if (raiz == NULL)
    return;
  if (*raiz != NULL)
  {
    emOrdem_ArvAVL(&((*raiz)->esq));
    printf("%d ", (*raiz)->info);
    emOrdem_ArvAVL(&((*raiz)->dir));
  }
}

void posOrdem_ArvAVL(ArvAVLRedBlack *raiz)
{
  if (raiz == NULL)
    return;
  if (*raiz != NULL)
  {
    posOrdem_ArvAVL(&((*raiz)->esq));
    posOrdem_ArvAVL(&((*raiz)->dir));
    printf("%d ", (*raiz)->info);
  }
}

int consulta_ArvAVL(ArvAVLRedBlack *raiz, int valor)
{
  if (raiz == NULL)
    return 0;
  struct NO *atual = *raiz;
  while (atual != NULL)
  {
    if (valor == atual->info)
    {
      return 1;
    }
    if (valor > atual->info)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
  return 0;
}

void RotacaoLL(ArvAVLRedBlack *A)
{ //LL
  if (DEBUG)
    printf("RotacaoLL\n");
  struct NO *B;
  B = (*A)->esq;
  (*A)->esq = B->dir;
  B->dir = *A;
  (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
  B->altura = maior(altura_NO(B->esq), (*A)->altura) + 1;
  *A = B;
}

void RotacaoRR(ArvAVLRedBlack *A)
{ //RR
  if (DEBUG)
    printf("RotacaoRR\n");
  struct NO *B;
  B = (*A)->dir;
  (*A)->dir = B->esq;
  B->esq = (*A);
  (*A)->altura = maior(altura_NO((*A)->esq), altura_NO((*A)->dir)) + 1;
  B->altura = maior(altura_NO(B->dir), (*A)->altura) + 1;
  (*A) = B;
}

void RotacaoLR(ArvAVLRedBlack *A)
{ //LR
  RotacaoRR(&(*A)->esq);
  RotacaoLL(A);
}

void RotacaoRL(ArvAVLRedBlack *A)
{ //RL
  RotacaoLL(&(*A)->dir);
  RotacaoRR(A);
}

int insere_ArvAVL(ArvAVLRedBlack *raiz, int valor)
{
  int res;
  if (*raiz == NULL)
  {
    struct NO *novo;
    novo = (struct NO *)malloc(sizeof(struct NO));
    if (novo == NULL)
      return 0;

    novo->info = valor;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    *raiz = novo;
    return 1;
  }

  struct NO *atual = *raiz;
  if (valor < atual->info)
  {
    if ((res = insere_ArvAVL(&(atual->esq), valor)) == 1)
    {
      if (fatorBalanceamento_NO(atual) >= 2)
      {
        if (valor < (*raiz)->esq->info)
        {
          RotacaoLL(raiz);
        }
        else
        {
          RotacaoLR(raiz);
        }
      }
    }
  }
  else
  {
    if (valor > atual->info)
    {
      if ((res = insere_ArvAVL(&(atual->dir), valor)) == 1)
      {
        if (fatorBalanceamento_NO(atual) >= 2)
        {
          if ((*raiz)->dir->info < valor)
          {
            RotacaoRR(raiz);
          }
          else
          {
            RotacaoRL(raiz);
          }
        }
      }
    }
    else
    {
      if (DEBUG)
        printf("Valor duplicado!\n");
      return 0;
    }
  }

  atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;

  return res;
}

struct NO *procuraMenor(struct NO *atual)
{
  struct NO *no1 = atual;
  struct NO *no2 = atual->esq;
  while (no2 != NULL)
  {
    no1 = no2;
    no2 = no2->esq;
  }
  return no1;
}

int remove_ArvAVL(ArvAVLRedBlack *raiz, int valor)
{
  if (*raiz == NULL)
  {
    if (DEBUG)
      printf("\n Este valor não existe na árvore!");
    return 0;
  }
  int res;
  if (valor < (*raiz)->info)
  {
    if ((res = remove_ArvAVL(&(*raiz)->esq, valor)) == 1)
    {
      if (fatorBalanceamento_NO(*raiz) >= 2)
      {
        if (altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
          RotacaoRR(raiz);
        else
          RotacaoRL(raiz);
      }
    }
  }

  if ((*raiz)->info < valor)
  {
    if ((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1)
    {
      if (fatorBalanceamento_NO(*raiz) >= 2)
      {
        if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
          RotacaoLL(raiz);
        else
          RotacaoLR(raiz);
      }
    }
  }

  if ((*raiz)->info == valor)
  {
    if (((*raiz)->esq == NULL || (*raiz)->dir == NULL))
    {
      struct NO *oldNode = (*raiz);
      if ((*raiz)->esq != NULL)
        *raiz = (*raiz)->esq;
      else
        *raiz = (*raiz)->dir;
      free(oldNode);
    }
    else
    {
      struct NO *temp = procuraMenor((*raiz)->dir);
      (*raiz)->info = temp->info;
      remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
      if (fatorBalanceamento_NO(*raiz) >= 2)
      {
        if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
          RotacaoLL(raiz);
        else
          RotacaoLR(raiz);
      }
    }
    if (*raiz != NULL)
      (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
    return 1;
  }

  (*raiz)->altura = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;

  return res;
}

// RedBlack
int corNo_ArvRedBlack(ArvAVLRedBlack *raiz, int valor)
{
  if (raiz == NULL)
    return BLACK;
  struct NO *atual = *raiz;
  while (atual != NULL)
  {
    if (valor == atual->info)
    {
      return atual->cor;
    }
    if (valor > atual->info)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
  return -1;
}

void preOrdem_ArvRedBlack(ArvAVLRedBlack *raiz)
{
  if (raiz == NULL)
    return;
  if (*raiz != NULL)
  {
    char cor = (*raiz)->cor == BLACK ? 'B' : 'R';
    printf("%d(%c) ", (*raiz)->info, cor);
    preOrdem_ArvRedBlack(&((*raiz)->esq));
    preOrdem_ArvRedBlack(&((*raiz)->dir));
  }
}

void emOrdem_ArvRedBlack(ArvAVLRedBlack *raiz)
{
  if (raiz == NULL)
    return;
  if (*raiz != NULL)
  {
    emOrdem_ArvRedBlack(&((*raiz)->esq));
    printf("%d ", (*raiz)->info);
    emOrdem_ArvRedBlack(&((*raiz)->dir));
  }
}

void posOrdem_ArvRedBlack(ArvAVLRedBlack *raiz)
{
  if (raiz == NULL)
    return;
  if (*raiz != NULL)
  {
    posOrdem_ArvRedBlack(&((*raiz)->esq));
    posOrdem_ArvRedBlack(&((*raiz)->dir));
    printf("%d ", (*raiz)->info);
  }
}

int consulta_ArvRedBlack(ArvAVLRedBlack *raiz, int valor)
{
  if (raiz == NULL)
    return 0;
  struct NO *atual = *raiz;
  while (atual != NULL)
  {
    if (valor == atual->info)
    {
      return 1;
    }
    if (valor > atual->info)
      atual = atual->dir;
    else
      atual = atual->esq;
  }
  return 0;
}

int insere_ArvRedBlack(ArvAVLRedBlack *raiz, int valor)
{
  int res = 0;
  res = insere(raiz, valor);
  (*raiz)->cor = BLACK;
  return res;
}

int insere(ArvAVLRedBlack *raiz, int valor)
{

  int res = 0;
  if (*raiz == NULL)
  {
    struct NO *novo;
    novo = (struct NO *)malloc(sizeof(struct NO));
    if (novo == NULL)
      return 0;

    novo->info = valor;
    novo->cor = RED;
    novo->esq = NULL;
    novo->dir = NULL;
    *raiz = novo;
    return 1;
  }

  if (valor < (*raiz)->info)
  {
    res = insere(&((*raiz)->esq), valor);
  }
  else if (valor > (*raiz)->info)
  {
    res = insere(&((*raiz)->dir), valor);
  }
  else
  {
    if (DEBUG)
      printf("Valor duplicado!\n");
    return 0;
  }

  if (isRed((*raiz)->dir) && !isRed((*raiz)->esq))
    *raiz = rotateLeft(*raiz);
  if (isRed((*raiz)->esq) && isRed((*raiz)->esq->esq))
    *raiz = rotateRight(*raiz);
  if (isRed((*raiz)->esq) && isRed((*raiz)->dir))
    flipColors(*raiz);

  return res;
}

struct NO *rotateLeft(struct NO *h)
{
  struct NO *x = h->dir;
  h->dir = x->esq;
  x->esq = h;
  x->cor = h->cor;
  h->cor = RED;
  if (DEBUG)
    printf("Rotate Left \n");
  return x;
}

struct NO *rotateRight(struct NO *h)
{
  struct NO *x = h->esq;
  h->esq = x->dir;
  x->dir = h;
  x->cor = h->cor;
  h->cor = RED;
  if (DEBUG)
    printf("Rotate Right \n");
  return x;
}

int remove_ArvRedBlack(ArvAVLRedBlack *raiz, int valor)
{
  return 1;
}

void flipColors(struct NO *h)
{
  h->cor = RED;
  h->esq->cor = BLACK;
  h->dir->cor = BLACK;
  if (DEBUG)
    printf("Flip colors \n");
}

int isRed(struct NO *h)
{
  if (h == NULL)
  {
    return 0;
  }
  return h->cor == RED ? 1 : 0;
}