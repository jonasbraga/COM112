#include <stdio.h>
#include <stdlib.h>

void leVetor(int *v, int n);
void insertionSort(int *v, int n);

int main() {
  int arrayLength = 0, *numbersArray;

  scanf("%d", &arrayLength);
  numbersArray = (int *) malloc(arrayLength * sizeof(int));

  leVetor(numbersArray, arrayLength);

  return 0;
}

void leVetor(int *v, int n){
  
  int i;

  for(i = 0; i < n; i++){
    scanf("%d", v + i);
  }

  insertionSort(v, n);
}

void insertionSort(int *v, int n){
  
  int i, j, aux, switches = 0, compares = 0;

  for (i = 1; i < n ; i++){
    aux = v[i];
    j = i - 1;
    while (j >= 0) {
      compares++;

      if(aux >= v[j]) break;

      switches++;
      v[j+1] = v[j];
      j--;
    }

    v[j+1] = aux;
  }

  printf("%d %d", compares, switches);
}