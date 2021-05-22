#include <stdio.h>
#include <stdlib.h>

void leVetor(int *v, int n);
void smartBubbleSort(int *v, int n);

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

  smartBubbleSort(v, n);
}

void smartBubbleSort(int *v, int n)
{
    int i, j, temp, switches = 0, compares = 0, swap = 1;
    for(i = 0; i <= n; i++) {
        if (i) printf("%d ", v[i-1]);
        if (!swap) continue;
        swap = 0;
        for(j = n - 1; j > i; j--) {
            compares++;
            if(v[j] > v[j-1]) {
                swap = 1;
                switches++;
                temp = v[j];
                v[j] = v[j-1];
                v[j-1] = temp;
            } 
        }
    }
   
    printf("\n%d %d", compares, switches);
}