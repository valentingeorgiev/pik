#include <stdio.h>
#include <stdlib.h>

void arrayAdding(int **arr) {
  int i=0;
  *arr = (int*) malloc(sizeof(int)*10);

  for (i = 0; i < 10; i++) {
    (*arr)[i]=i+10;
  }
}

void print(int **arr){
  int i=0;
  for (i = 0; i < 10; i++) {
    printf("%d\n", (*arr)[i]*100);
  }
}

int main() {
  int *arr=NULL;
  int i=0;

  arrayAdding(&arr);
  print(&arr);
  return 0;
}

