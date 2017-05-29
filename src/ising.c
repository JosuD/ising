#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "metropolis.h"
#include "lattice.h"
#include "math.h"

int main(int argc, char **argv) {
  int n = 5;
  int aceptados = 0;
  int i,j, t;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float T = 1.0;
  float dE = 0.0;
  float dM = 0.0;
  float* dE_dM;
  int niter = 10000;
  int niter_terma = 10000;
  int nT = 100;
  int nfinal = 3000;
  int* sitiostest = malloc(niter*sizeof(int));
  float* linspace_T = malloc(nT*sizeof(float));
  float* energia = malloc(nT*sizeof(float));
  float* magnetizacion = malloc(nT*sizeof(float));
  float* E_terma = malloc(nfinal*sizeof(float));
  float* M_terma = malloc(nfinal*sizeof(float));
  float energia_iter = 0.0;
  float magnetizacion_iter = 0.0;
  float B = 0.0;
  float J = 1.0;
  float gap_E = 0.0;
  float* lut = malloc(5*sizeof(float));
  float paso = 5.0/nT;
  *linspace_T = 0.001;
  for(i=1; i<nT-1; i++){
    *(linspace_T+i) = *(linspace_T+i-1) + paso;
  }

  srand(time(NULL));
  fill_lattice(lattice, n, 0.9999);
  print_lattice(lattice, n);
  //*E_terma = calc_energia(lattice, n, B, J);
  //*M_terma = calc_magnet(lattice, n);
  *energia = calc_energia(lattice, n, B, J);
  *magnetizacion = calc_magnet(lattice, n);
  for(j=1; j<nT; j++){
    printf("Temperatura %d/%d\n", j, nT);
    for(i=1; i<nfinal; i++){
      dE_dM = metropolis(lattice, n, *(linspace_T+j), B, J, lut);
      //printf("dE=%f, dM = %f\n",*dE_dM, *(dE_dM+1) );
      //*(E_terma+i) = *(E_terma+i-1)+*dE_dM;
      //*(M_terma+i) = *(M_terma+i-1)+*(dE_dM + 1);
      //print_lattice(lattice,n);
    }
    dE_dM = metropolis(lattice, n, *(linspace_T+j), B, J, lut);
    *(magnetizacion+j) = *(magnetizacion+j-1) + *(dE_dM+1);
    *(energia+j) = *(energia+j-1) + *dE_dM;
  }
  print_lattice(lattice, n);
  printf("Exportando...\n");
  //exportar_vector_float(E_terma, nfinal, "energia.txt");
  //exportar_vector_float(M_terma, nfinal, "magnetizacion.txt");
  exportar_vector_float(energia, nT, "energia.txt");
  exportar_vector_float(magnetizacion, nT, "magnetizacion.txt");
  return 0;
}
