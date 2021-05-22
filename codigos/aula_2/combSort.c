#include <stdio.h>
#include <stdlib.h>

void readVetorByFileName(int *v, int n);
void combSort(int *v, int n);

int main() {
  int arrayLength = 0, *numbersArray;

  scanf("%d", &arrayLength);
  numbersArray = (int *) malloc(arrayLength * sizeof(int));

  readVetorByFileName(numbersArray, arrayLength);

  return 0;
}

void readVetorByFileName(int *v, int n){    
  
  // TODO

  combSort(v, n);
}

void combSort(int *v, int n){ 
  int step = n, temp, compares = 0, switches = 0; 
  while (step != 1){ 
    step = (int)step/1.3; 
    if (step < 1) step = 1;
    for (int i = 0; i < n-step; i++){ 
      compares++;
      if (v[i] > v[i+step]) {
        switches++;
        temp = v[i];
        v[i] = v[i+step];
        v[i+step] = temp;
      }
    } 
  } 

  printf("\n%d %d", compares, switches);
} 
