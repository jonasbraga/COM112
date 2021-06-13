void selectionSort(int *v, int n){
  int i, j, aux, minIndex;

  for (i = 0; i < (n - 1); i++){
    minIndex = i;

    for (j = i + 1; j < n; j++){
      compares++;
      if (v[j] < v[minIndex]) minIndex = j;
    }
    
    swap(&v[i], &v[minIndex]);
  }
}
