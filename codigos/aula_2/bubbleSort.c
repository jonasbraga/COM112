#include <stdio.h>
#include <stdlib.h>

void leVetor(int *v, int n);
void bubbleSort(int *v, int n);

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

  bubbleSort(v, n);
}

void bubbleSort(int *v, int n)
{
    int i, j, temp, switches = 0, compares = 0;
    for(i = 0; i < n; i++) {
        for(j = n - 1; j > i; j--) {
            compares++;
            if(v[j] < v[j-1]) {
                switches++;
                temp = v[j];
                v[j] = v[j-1];
                v[j-1] = temp;
            } 
        }
    }
   
    printf("%d %d", compares, switches);
}