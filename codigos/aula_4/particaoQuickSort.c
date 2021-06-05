#include <stdio.h>
#include <stdlib.h>

void leVetor(int *v, int n);
void quickSortHoare(int *v, int p, int r, int (*partitionFunction)());
void quickSort(int *v, int p, int r, int (*partitionFunction)());
int particaoHoare(int *v, int p, int r);
int particaoLomuto(int *v, int p, int r);
int particaoSedgewick(int *v, int p, int r);
void swap(int* a, int* b);

typedef int (*fParticao)(int *, int, int); 
typedef void (*fQuickSort)(int *, int, int, int()); 

int switches = 0, compares = 0;

int main() {
  int arrayLength = 0, *numbersMatrix;

  scanf("%d", &arrayLength);
  
  numbersMatrix = (int *)malloc(3 * arrayLength * sizeof(int));

  leVetor(numbersMatrix, arrayLength);

  fParticao funcPart[3] = {&particaoHoare, &particaoLomuto, &particaoSedgewick};
  fQuickSort funcQS[3] = {&quickSortHoare, &quickSort, &quickSort};

  for(int i = 0; i < 3; i++) {
    switches = 0; compares = 0;
    
    (*funcQS[i])(numbersMatrix, i * arrayLength, (i + 1) * arrayLength - 1, funcPart[i]);

    printf("%d %d\n", compares, switches);
  }

  free(numbersMatrix);

  return 0;
}

void leVetor(int *v, int n) { 
  int temp = 0;
  for(int i = 0; i < n; i++){
    scanf("%d", &temp);
    for(int j = 0; j < 3; j++) v[j * n + i] = temp;
  }
}

void quickSortHoare(int *v, int p, int r, int (*partitionFunction)()){
  if (p < r){
    int pi = (*partitionFunction) (v, p, r);    
    quickSortHoare(v, p, pi, partitionFunction);
    quickSortHoare(v, pi + 1, r, partitionFunction);
  }
}

void quickSort(int *v, int p, int r, int (*partitionFunction)()){
  if (p < r){
    int pi = (*partitionFunction) (v, p, r);    
    quickSort(v, p, pi - 1, partitionFunction);
    quickSort(v, pi + 1, r, partitionFunction);
  }
}

int particaoHoare(int *v, int p, int r){
  int i = p - 1, j = r + 1, piv = v[p];
  
  while(1){
    do {
      i++;
      compares++;
    } while (v[i] < piv);

    do {
      j--;
      compares++;
    } while (v[j] > piv);

    if(i >= j) return j;

    swap(&v[i], &v[j]);
  } 
  return 1;
}

int particaoLomuto(int *v, int p, int r){
  int i = p - 1, j = p, piv = v[r];
  for(j = p; j <= r - 1; j++){
    compares++;
    if(v[j] <= piv) swap(&v[++i], &v[j]);
  }

  swap(&v[i + 1], &v[r]);

  return i + 1;
}

int particaoSedgewick(int *v, int p, int r){
  int i = p, j = r + 1, piv = v[p];

  while(1){
    compares++;
    while(v[++i] < piv) {
      if(i == r) break;
      compares++;
    }
    compares++;
    while(piv < v[--j]) {
      if(j == p) break;
      compares++;
    }

    if(i >= j) break;

    swap(&v[i], &v[j]);
  }
  swap(&v[p], &v[j]);
  return j;
}

void swap(int* a, int* b){
  switches++;
  int t = *a;
  *a = *b;
  *b = t;
}