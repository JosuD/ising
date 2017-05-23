#include "stdio.h"
#include "stdlib.h"
int* puntero(int a, int b);

int main(){

  int a, b, *ambos;
  a = 5;
  b = 9;
  //printf("hasta aca todo bien\n");
  ambos = puntero(a,b);
  printf("a = %d, b = %d\n", *ambos, *(ambos+1));
  return 1;

}

int* puntero(int a, int b){
  int *ambos;
  ambos = malloc(2*sizeof(int));
  *ambos = a;
  *(ambos+1) = b;
  printf("funcion puntero ha funcionado, felicitaciones\n");
  return ambos;
}
