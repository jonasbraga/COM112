// gcc ./codigos/trabalho_1/main.c -o exe -lm && ./exe

#include "utils.c"

#include "bubbleSort.c" // 1
#include "combSort.c" // 1
#include "insertionSort.c" // 1
#include "selectionSort.c" // 1
#include "mergeSort.c" // 2
#include "quickSort.c" // 1
#include "rapidSort.c" // 5
#include "radixSort.c" // 3

int main(){
  //RANDOM_ARRAY
  // executeSortAlgorithm(&bubbleSort, massas[RANDOM_ARRAY][0], massas[RANDOM_ARRAY][0][ARRAY_LENGTH_INDEX], 0, 0);
  //  executeSortAlgorithm(&bubbleSort, massas[RANDOM_ARRAY][1], massas[RANDOM_ARRAY][1][ARRAY_LENGTH_INDEX], 0, 0);
  // executeSortAlgorithm(&bubbleSort, massas[RANDOM_ARRAY][2], massas[RANDOM_ARRAY][2][ARRAY_LENGTH_INDEX], 0, 0);
  // executeSortAlgorithm(&bubbleSort, massas[RANDOM_ARRAY][3], massas[RANDOM_ARRAY][3][ARRAY_LENGTH_INDEX], 0, 0);
  // executeSortAlgorithm(&bubbleSort, massas[RANDOM_ARRAY][4], massas[RANDOM_ARRAY][4][ARRAY_LENGTH_INDEX], 0, 0);

  //SORTED_ARRAY
  // executeSortAlgorithm(&bubbleSort, massas[SORTED_ARRAY][0], massas[SORTED_ARRAY][0][ARRAY_LENGTH_INDEX], 0, 0);
  // executeSortAlgorithm(&bubbleSort, massas[SORTED_ARRAY][1], massas[SORTED_ARRAY][1][ARRAY_LENGTH_INDEX], 0, 0);
  // executeSortAlgorithm(&bubbleSort, massas[SORTED_ARRAY][2], massas[SORTED_ARRAY][2][ARRAY_LENGTH_INDEX], 0, 0);
  // executeSortAlgorithm(&bubbleSort, massas[SORTED_ARRAY][3], massas[SORTED_ARRAY][3][ARRAY_LENGTH_INDEX], 0, 0);
  // executeSortAlgorithm(&bubbleSort, massas[SORTED_ARRAY][4], massas[SORTED_ARRAY][4][ARRAY_LENGTH_INDEX], 0, 0);

  //REVERSE_SORTED_ARRAY
  // executeSortAlgorithm(&bubbleSort, massas[REVERSE_SORTED_ARRAY][0], massas[REVERSE_SORTED_ARRAY][0][ARRAY_LENGTH_INDEX], 0, 0);
  // executeSortAlgorithm(&bubbleSort, massas[REVERSE_SORTED_ARRAY][1], massas[REVERSE_SORTED_ARRAY][1][ARRAY_LENGTH_INDEX], 0, 0);
  executeSortAlgorithm(&bubbleSort, massas[REVERSE_SORTED_ARRAY][2], massas[REVERSE_SORTED_ARRAY][2][ARRAY_LENGTH_INDEX], 0, 0);
  /* executeSortAlgorithm(&bubbleSort, massas[REVERSE_SORTED_ARRAY][3], massas[REVERSE_SORTED_ARRAY][3][ARRAY_LENGTH_INDEX], 0, 0);
  executeSortAlgorithm(&bubbleSort, massas[REVERSE_SORTED_ARRAY][4], massas[REVERSE_SORTED_ARRAY][4][ARRAY_LENGTH_INDEX], 0, 0);

  //RANDOM_REPEATED_ELEMENTS_ARRAY
  executeSortAlgorithm(&bubbleSort, massas[RANDOM_REPEATED_ELEMENTS_ARRAY][0], massas[RANDOM_ARRAY][0][ARRAY_LENGTH_INDEX], 0, 0);
  executeSortAlgorithm(&bubbleSort, massas[RANDOM_REPEATED_ELEMENTS_ARRAY][1], massas[RANDOM_ARRAY][1][ARRAY_LENGTH_INDEX], 0, 0);
  executeSortAlgorithm(&bubbleSort, massas[RANDOM_REPEATED_ELEMENTS_ARRAY][2], massas[RANDOM_ARRAY][2][ARRAY_LENGTH_INDEX], 0, 0);
  executeSortAlgorithm(&bubbleSort, massas[RANDOM_REPEATED_ELEMENTS_ARRAY][3], massas[RANDOM_ARRAY][3][ARRAY_LENGTH_INDEX], 0, 0);
  executeSortAlgorithm(&bubbleSort, massas[RANDOM_REPEATED_ELEMENTS_ARRAY][4], massas[RANDOM_ARRAY][4][ARRAY_LENGTH_INDEX], 0, 0); */


//  imprimeVetor(massas[RANDOM_ARRAY][0], massas[RANDOM_ARRAY][0][ARRAY_LENGTH_INDEX]);

  return 0;
}