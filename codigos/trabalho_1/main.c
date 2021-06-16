// gcc ./codigos/trabalho_1/main.c -o exe -lm && ./exe

#include "utils.c"

#include "bubbleSort.c"
#include "combSort.c"
#include "insertionSort.c"
#include "selectionSort.c"
#include "mergeSort.c"
#include "quickSort.c"
#include "rapidSort.c"
#include "radixSort.c"

int main(){
  executeSortAlgorithm(&rapidSort, massas[RANDOM_ARRAY][0], massas[RANDOM_ARRAY][0][ARRAY_LENGTH_INDEX], 0, 0);
  executeSortAlgorithm(&radixSort, massas[RANDOM_ARRAY][0], massas[RANDOM_ARRAY][0][ARRAY_LENGTH_INDEX], 0, 0);
  
  // imprimeVetor(massas[RANDOM_ARRAY][0], massas[RANDOM_ARRAY][0][ARRAY_LENGTH_INDEX]);

  return 0;
}