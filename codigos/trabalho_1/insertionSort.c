void insertionSort(int *v, int n){
  
  int i, j, aux;

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
}