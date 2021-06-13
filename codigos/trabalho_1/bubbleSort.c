void bubbleSort(int *v, int n) {
  int i, j;
  for(i = 0; i < n; i++) {
    for(j = n - 1; j > i; j--) {
      compares++;
      if(v[j] < v[j-1]) {
        swap(&v[j], &v[j-1]);
      } 
    }
  }
}