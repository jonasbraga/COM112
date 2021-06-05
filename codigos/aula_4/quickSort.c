#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
  char nome[1000];
  char curso[4];
  int matricula;
} aluno;

void imprimeVetor(aluno *v, int n);
void leVetor(aluno *v, char *nomeArquivo);
int particao(aluno *v, int p, int r);
void quickSort(aluno *v, int p, int r);
void swap(aluno* a, aluno* b);

int quantAlunos = 0; 

int main() {
  char nomeArquivo[500] = {' '};
  aluno alunos[1000];

  scanf(" %[^\n]s", nomeArquivo);
   
  leVetor(alunos, nomeArquivo);
  
  quickSort(alunos, 0, quantAlunos - 1);

  imprimeVetor(alunos, quantAlunos);

  return 0;
}

void imprimeVetor(aluno *v, int n){
  for(int i = 0; i < n; i++){
    printf("%s %s %d\n", v[i].nome, v[i].curso, v[i].matricula);
  }
}

void leVetor(aluno *v, char *nomeArquivo){
  int i = 0;
  char studentData[2000];
  FILE *studentFile = NULL;

  studentFile = fopen(nomeArquivo, "r");
  if(studentFile == NULL) printf(" Deu erro");

  while(fgets(studentData, 2000, studentFile)){

    char *splitedStudentData = strtok(studentData, "\t");
    
    for(int j = 0; j < 3; j++){
      if(j == 0) strcpy(v[i].nome, splitedStudentData);
      else if(j == 1) strcpy(v[i].curso, splitedStudentData);
      else if(j == 2) v[i].matricula = atoi(splitedStudentData);
      
      splitedStudentData = strtok(NULL, "\t");
    }
    i++;
  }
  quantAlunos = i;
}

int particao(aluno *v, int p, int r){
  int i = (p - 1), j = p, equal = 0, nameLength = strlen(v[r].nome);
  int *pivot = (int *) malloc(nameLength * sizeof(int));

  for(int i = 0; i < nameLength; i++){
    pivot[i] = (int)v[r].nome[i];
  }

  while(j <= r - 1){
    if((int)v[j].nome[equal] == pivot[equal]){
      equal++;
      continue;
    }
    if ((int)v[j].nome[equal] < pivot[equal]){
      i++; 
      swap(&v[i], &v[j]);
    }
    equal = 0;
    j++;
  }
  free(pivot);
  swap(&v[i + 1], &v[r]);
  return (i + 1);
}

void quickSort(aluno *v, int p, int r){
  if (p < r){
    int pi = particao(v, p, r);
    quickSort(v, p, pi - 1);
    quickSort(v, pi + 1, r);
  }
}

void swap(aluno* a, aluno* b){
  aluno t = *a;
  *a = *b;
  *b = t;
}