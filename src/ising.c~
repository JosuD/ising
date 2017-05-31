#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "metropolis.h"
#include "lattice.h"
#include "math.h"

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
  int niter = 10000;
  int niter_terma = 10000;
  int nT = 100;
  int nfinal = 50000;
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
  fill_lattice(lattice, n, 0.999);
  print_lattice(lattice, n);
  *energia = calc_energia(lattice, n, B, J);
  *magnetizacion = calc_magnet(lattice, n);

  // Comienzo a iterar para cada T
  for(t=1; t<nT-1; t++){
    // Inicializo valores de la iteración
    printf("Temperatura %d/%d\n",t, nT);
    energia_iter = *(energia+t-1);
    magnetizacion_iter = *(magnetizacion+t-1);
    aceptados = 0;
    // Preparo el vector LUT con las exponenciales para cada T
    for(i=0; i<5; i++){
      gap_E = (float)(-2* (-J* (-4.0+2.0*i) -B ));//(float)(n*n*4);
      *(lut+i) = expf(-(float)gap_E / *(linspace_T+t));
      //printf("lut + %d = %f\n",i, *(lut+i) );
    }
    // Termalizo para cada T
    for(j = 0; j<niter_terma; j++){
      dE_dM = metropolis(lattice, n, *(linspace_T+t), B, J, lut); // pasos de termalización
    }
    // Itero haciendo metrópolis y acumulando las variaciones de dE, dM
    for(i = 0; i < niter; i++){
      dE_dM = metropolis(lattice, n, *(linspace_T+t), B, J, lut);
      dE = (float)(*dE_dM);
      dM = (float)(*(dE_dM+1));
      energia_iter += dE;
      magnetizacion_iter += dM;
      if(dE != 0.0) aceptados ++;
      //printf("iter = %d , dE = %f, dM = %f\n",i, energia_iter,magnetizacion_iter );
    }
    *(energia + t) =  energia_iter; //+ *(energia+t-1);
    *(magnetizacion + t) =  magnetizacion_iter; //+ *(magnetizacion+t-1);
    //printf("aceptados = %d/%d\n", aceptados, niter);
    //printf("\n");
    //printf("magnetizacion= %f, magnetizacion_iter = %f\n", *(magnetizacion+t), magnetizacion_iter);
    //printf("energia= %f, energia_iter = %f\n", *(energia+t), energia_iter);
  }
    *E_terma = calc_energia(lattice, n, B, J);
    *M_terma = calc_magnet(lattice, n);
    for(i=1; i<nfinal; i++){
      dE_dM = metropolis(lattice, n, 4.0, B, J, lut);
      *(E_terma+i) = *(E_terma+i-1)+*dE_dM;
      *(M_terma+i) = *(M_terma+i-1)+*(dE_dM + 1);
    }

  print_lattice(lattice, n);
  printf("Exportando...\n");
  exportar_vector_float(E_terma, nfinal, "energia.txt");
  exportar_vector_float(M_terma, nfinal, "magnetizacion.txt");
  //exportar_vector_float(energia, nT, "energia.txt");
  //exportar_vector_float(magnetizacion, nT, "magnetizacion.txt");
  return 0;
}
