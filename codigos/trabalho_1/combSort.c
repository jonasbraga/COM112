void combSort(int *v, int n){ 
  int step = n, temp; 
  while (step != 1){ 
    step = (int)step/1.3; 
    if (step < 1) step = 1;
    for (int i = 0; i < n-step; i++){ 
      compares++;
      if (v[i] > v[i+step]) swap(&v[i], &v[i+step]);
    } 
  } 
} 