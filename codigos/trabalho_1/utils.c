#define MIN_ARRAYS_LENGTH 75000 + 1 // + 1 para armazenar o length no 1º elemento do array
#define TOTAL_ARRAYS_PER_THEME 5
#define TOTAL_ARRAYS_THEME 4
#define RANDOM_ARRAY 0
#define SORTED_ARRAY 1
#define REVERSE_SORTED_ARRAY 2
#define RANDOM_REPEATED_ELEMENTS_ARRAY 3
#define ARRAY_LENGTH_INDEX -1

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "sys/time.h"

// ===== Massas de testes =====

#include "arrays.c"

int *massas[4][5] = {
  {
    &randomArray[0][1],
    &randomArray[1][1],
    &randomArray[2][1],
    &randomArray[3][1],
    &randomArray[4][1]
  },
  {
    &sortedArray[0][1],
    &sortedArray[1][1],
    &sortedArray[2][1],
    &sortedArray[3][1],
    &sortedArray[4][1]
  },
  {
    &reverseSortedArray[0][1],
    &reverseSortedArray[1][1],
    &reverseSortedArray[2][1],
    &reverseSortedArray[3][1],
    &reverseSortedArray[4][1]
  },
  {
    &randomRepeatedElementsArray[0][1],
    &randomRepeatedElementsArray[1][1],
    &randomRepeatedElementsArray[2][1],
    &randomRepeatedElementsArray[3][1],
    &randomRepeatedElementsArray[4][1]
  }
};

// ===== Variáveis globais de controle =====

long int switches = 0, compares = 0;
time_t startedMoment;
double elapsedSeconds = 0;

// ===== Funções úteis =====

void imprimeVetor(int *v, int n) {
  printf("Array ordenado: \n[");
  for(int i = 0; i < n; i++) {
    if(i + 1 < n) printf("%d, ", v[i]);
    else printf("%d", v[i]);
  }
  printf("]\n");
  printf("%d elementos\n", n);
}

void swap(int* a, int* b){
  switches++;
  int t = *a;
  *a = *b;
  *b = t;
}
struct timeval begin, end;
void startTimer() {
  gettimeofday(&begin, 0);
  startedMoment = time(NULL);
}

void calculateExecutionTime() {
  gettimeofday(&end, 0);
  long seconds = end.tv_sec - begin.tv_sec;
  long microseconds = end.tv_usec - begin.tv_usec;
  elapsedSeconds = seconds + microseconds*1e-6;
}

void showAlgorithmReport(){
  printf("Comparações: \t %ld \n", compares);
  printf("Trocas: \t\t %ld \n", switches);
  printf("Tempo: \t\t\t %f s \n", elapsedSeconds);
}

void executeSortAlgorithm(void (*sortFunction)(), int *elements, int length, int isMerge, int isQuick){
  compares = 0;
  switches = 0;

  startTimer();

  if(isMerge || isQuick) (*sortFunction)(elements, 0, isQuick ? length - 1 : length);
  else (*sortFunction)(elements, length);

  calculateExecutionTime();

  showAlgorithmReport();
}