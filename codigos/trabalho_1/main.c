// gcc ./codigos/trabalho_1/main.c -o exe -lm && ./exe

#include "utils.c"

#include "bubbleSort.c"
#include "combSort.c"
#include "insertionSort.c"
#include "selectionSort.c"
#include "mergeSort.c"
#include "quickSort.c"

int main(){

  executeSortAlgorithm(&bubbleSort, massas[RANDOM_ARRAY][0], massas[RANDOM_ARRAY][0][ARRAY_LENGTH_INDEX], 0, 0);

  return 0;
}