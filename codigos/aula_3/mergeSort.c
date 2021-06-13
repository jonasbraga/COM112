#include <stdio.h>
#include <stdlib.h>

void leVetor(int *v, int n);
void mergeSort(int *v, int p, int r);
void intercala(int *v, int p, int q, int r);

int switches = 0, compares = 0;

int main() {
  int arrayLength = 0, *numbersArray;

  scanf("%d", &arrayLength);
  numbersArray = (int *) malloc(arrayLength * sizeof(int));

  leVetor(numbersArray, arrayLength);

  return 0;
}

void leVetor(int *v, int n) { 
  
  int i;

  for(i = 0; i < n; i++){
    scanf("%d", v + i);
  }

  mergeSort(v, 0, n);

  printf("%d %d", compares, switches);
}

void mergeSort(int *v, int p, int r) {
	if(p < r - 1) {
		int q = (p + r) / 2;
		mergeSort(v, p, q);
		mergeSort(v, q, r);
		intercala(v, p, q, r);
	}
}

void intercala(int *v, int p, int q, int r) {
	int i, j, k;
	int *w;

	w = (int *)malloc((r - p) * sizeof(int));
	i = p;
	j = q;
	k = 0;

	while(i < q && j < r) {
    compares++;
    switches++;
		if(v[i] <= v[j])
			w[k++] = v[i++];
		else
			w[k++] = v[j++];
	}

	while(i < q) {
    w[k++] = v[i++];
    switches++;
  }
	while(j < r){
    w[k++] = v[j++];
    switches++;
  }
	
	for(i = p; i < r; i++){
    v[i] = w[i - p];
    switches++;
  }

	free(w);
}