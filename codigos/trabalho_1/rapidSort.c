void rapidSort(int *arr, int n) {
  
  for (int i = 1; i < n; i++) {
    int x = arr[i];
    int j = i - 1;
    compares++;
    while(j >= 0 && x < arr[j]){
      compares++;
      switches++;
      arr[j+1] = arr[j];
      j--;
    }
    switches++;
    arr[j+1] = x;
  }
}