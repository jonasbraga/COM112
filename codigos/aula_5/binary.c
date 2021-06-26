#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
  int key;
  struct Node *left, *right;
  int n;
} Node;

Node* put(Node **x, int key);
void insert(Node **root, int key);
int size(Node *x);

int main(){
  Node *root = NULL;
  insert(&root, 50);
  return 0;
}

void insert(Node **root, int key) {
  (*root) = put(&(*root), key);
}

Node* put(Node **x, int key) {
  if(!(*x)) {
    (*x) = (Node *)malloc(sizeof(Node));
    (*x)->key = key;
    (*x)->left = (*x)->right = NULL;
    (*x)->n = 1;
    return (*x);
  }
  if(key < (*x)->key)
    (*x)->left = put(&(*x)->left, key);
  else
    (*x)->right = put(&(*x)->right, key);

  (*x)->n = 1 + size((*x)->left) + size((*x)->right);

  return (*x);
}

Node* busca(Node **x, int key, int p, int r) {
  while (p <= r) {
    int center = p + (r - p) / 2;

    if(key == (*x)->key) return (*x); 
  }

  return NULL;
}

int size(Node *x) {
  if(!x) return 0;
  else return x->n;
}