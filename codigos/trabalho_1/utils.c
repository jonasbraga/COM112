#define MIN_ARRAYS_LENGTH 20200 + 1 // + 1 para armazenar o length no 1º elemento do array
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

// ===== Massas de testes =====

int randomArray[TOTAL_ARRAYS_PER_THEME][MIN_ARRAYS_LENGTH] = {
  {50200, 10, 11, 12, 13},
  {20301, 10, 11, 12, 13},
  {20402, 10, 11, 12, 13},
  {20503, 10, 11, 12, 13},
  {20604, 10, 11, 12, 13}
};

int sortedArray[TOTAL_ARRAYS_PER_THEME][MIN_ARRAYS_LENGTH] = {
  {4, 1, 2, 3, 4},
  {4, 1, 2, 3, 4},
  {4, 1, 2, 3, 4},
  {4, 1, 2, 3, 4},
  {4, 1, 2, 3, 4}
};

int reverseSortedArray[TOTAL_ARRAYS_PER_THEME][MIN_ARRAYS_LENGTH] = {
  {4, 4, 3, 2, 1},
  {4, 4, 3, 2, 1},
  {4, 4, 3, 2, 1},
  {4, 4, 3, 2, 1},
  {4, 4, 3, 2, 1}
};

int randomRepeatedElementsArray[TOTAL_ARRAYS_PER_THEME][MIN_ARRAYS_LENGTH] = {
  {4, 10, 11, 12, 13},
  {4, 10, 11, 12, 13},
  {4, 10, 11, 12, 13},
  {4, 10, 11, 12, 13},
  {4, 10, 11, 12, 13}
};

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

// ===== Definição de novo tipo de funções =====

// typedef int (*fParticao)(int *, int, int); 
// typedef void (*fQuickSort)(int *, int, int, int()); 

// ===== Variáveis globais de controle =====

long int switches = 0, compares = 0;
time_t startedMoment;
double elapsedSeconds = 0;

// ===== Funções úteis =====

void imprimeVetor(int *v, int n) {
  for(int i = 0; i < n; i++) {
    printf("%d\n", v[i]);
  }
}

void swap(int* a, int* b){
  switches++;
  int t = *a;
  *a = *b;
  *b = t;
}

void startTimer() {
  startedMoment = time(NULL);
}

double calculateExecutionTime() {
  time_t endMoment = time(NULL);
  return elapsedSeconds = difftime(endMoment, startedMoment);  
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