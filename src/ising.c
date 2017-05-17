#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
  int n = 8;
  int aceptados = 0;
  int i;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 0.01;
  int niter = 10;
  int* sitiostest = malloc(niter*sizeof(int));
  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  for(i = 0; i < niter; i++){
    aceptados +=metropolis(lattice, n, T);
    //*(sitiostest+i) = pick_site(lattice, n);
    print_lattice(lattice, n);
    printf("\n");
  }
  printf("flipearon %d veces \n", aceptados);
  //exportar_vector_int(sitiostest, niter, "test.txt");
  return 0;
}
