#include "lattice.h"
#include "stdlib.h"
#include "stdio.h"
int fill_lattice(int *lattice, int n, float p) {
  int i,j;
  for(i=0;i<n;i++){
    for(j=0; j<n; j++){
      *(lattice+i*n+j) = randomspin(p);
      }
    }
  return 0;

}
int randomspin(float p){
  int val;
	float x;
	x = (float)rand()/((float)RAND_MAX); // Valor de distribución uniforme entre 0 y 1
	if(x<p)
		val = 1;
	else
		val = -1;
  return val;
}

int print_lattice(int *lattice, int n) {
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n-1; j++){
      printf("%d\t", *(lattice+i*n+j));
      }
    printf("%d\n", *(lattice+i*n+j));
	  }
  return 0;
}

void exportar_vector_int(int *vector, int n, char* nombre){
	int i;
	FILE *fp;
	fp = fopen(nombre, "a");
	for(i = 0; i< n-1; i++){
    fprintf(fp, "%d\t", *(vector+i));
		}
		fprintf(fp, "%d\n", *(vector+i));
	fclose(fp);
}
