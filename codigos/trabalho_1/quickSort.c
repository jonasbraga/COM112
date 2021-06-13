
int particaoSedgewick(int *v, int p, int r){
  int i = p, j = r + 1, piv = v[p];

  while(1){
    compares++;
    while(v[++i] < piv) {
      if(i == r) break;
      compares++;
    }
    compares++;
    while(piv < v[--j]) {
      if(j == p) break;
      compares++;
    }

    if(i >= j) break;

    swap(&v[i], &v[j]);
  }
  swap(&v[p], &v[j]);
  return j;
}

void quickSort(int *v, int p, int r){
  if (p < r){
    int pi = particaoSedgewick(v, p, r);    
    quickSort(v, p, pi - 1);
    quickSort(v, pi + 1, r);
  }
}