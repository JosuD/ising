#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
  int n = 8;
  int aceptados = 0;
  int i,j, t;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 1.0;
  float dE = 0.0;
  float dM = 0.0;
  float* dE_dM;
  int niter = 2000;
  int niter_terma = 5000;
  int nT = 1000;
  int* sitiostest = malloc(niter*sizeof(int));
  float* linspace_T = malloc(nT*sizeof(float));
  float* energia = malloc(nT*sizeof(float));
  float* magnetizacion = malloc(nT*sizeof(float));
  float energia_iter = 0.0;
  float magnetizacion_iter = 0.0;
  float paso = 5.0/nT;
  *linspace_T = 0.001;
  for(i=1; i<nT-1; i++){
    *(linspace_T+i) = *(linspace_T+i-1) + paso;
  }

  srand(time(NULL));
  fill_lattice(lattice, n, 0.999);
  print_lattice(lattice, n);
  *energia = calc_energia(lattice, n);
  *magnetizacion = calc_magnet(lattice, n);
  for(t=1; t<nT-1; t++){
    //printf("Temperatura %d/%d\n",t, nT);

    for(j = 0; j<niter_terma; j++){
      dE_dM = metropolis(lattice, n, *(linspace_T+t)); // pasos de termalización
    }

    for(i = 0; i < niter; i++){
      dE_dM = metropolis(lattice, n, *(linspace_T+t));
      dE = (float)(*dE_dM);
      dM = (float)(*(dE_dM+1));
      energia_iter += dE/(float)niter;
      magnetizacion_iter += dM/(float)niter;
    }
    *(energia + t) = *(energia+t-1) + energia_iter;
    *(magnetizacion + t) = *(magnetizacion+t-1) + magnetizacion_iter;
    printf("magnetizacion + t = %f, magnetizacion_iter = %f\n", *(magnetizacion+t), magnetizacion_iter);
  }


  printf("llegamos a armar los datos\n");
  exportar_vector_float(energia, nT, "energia.txt");
  exportar_vector_float(magnetizacion, nT, "magnetizacion.txt");
  return 0;
}
