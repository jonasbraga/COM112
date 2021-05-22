#include <stdio.h>
#include <stdlib.h>

void leVetor(int *v, int n);
void selectionSort(int *v, int n);

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

  selectionSort(v, n);
}

void selectionSort(int *v, int n){
  
  int i, j, aux, minIndex, switches = 0, compares = 0;

  for (i = 0; i < (n - 1); i++){
    minIndex = i;

    for (j = i + 1; j < n; j++){
      compares++;
      if (v[j] < v[minIndex]) minIndex = j;
    }

    switches++;
    aux = v[i];
    v[i] = v[minIndex];
    v[minIndex] = aux;
  }
  printf("%d %d", compares, switches);
}
