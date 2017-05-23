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
  float T = 1.0;
  float dE = 0.0;
  float dM = 0.0;
  int* dE_dM;
  int niter = 10000;
  int* sitiostest = malloc(niter*sizeof(int));
  float* energia = malloc(niter*sizeof(float));
  float* magnetizacion = malloc(niter*sizeof(float));

  srand(time(NULL));
  fill_lattice(lattice, n, prob);
  *energia = calc_energia(lattice, n);
  *magnetizacion = calc_magnet(lattice, n);
  for(i = 0; i < niter; i++){
    dE_dM = metropolis(lattice, n, T);
    dE = (float)(*dE_dM);
    dM = (float)(*(dE_dM+1));
    *(energia + i) = *(energia+i-1) + dE;
    *(magnetizacion+i) = *(magnetizacion+i-1) + dM;
  }
  //printf("flipearon %d veces \n", aceptados);
  exportar_vector_float(energia, niter, "energia.txt");
  exportar_vector_float(magnetizacion, niter, "magnetizacion.txt");
  return 0;
}
