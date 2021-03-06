#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "metropolis.h"
#include "lattice.h"
#include "math.h"

int main(int argc, char **argv) {

// Parámetros

  float B = 0.0;
  float J = 1.0;
  //float T_p = 1.0;
  int indice_T0 = 45;

// Declaraciones de todo lo demás

  int n = 32;
  int i,j,k;
  int *lattice = malloc(n * n * sizeof(int));
  float prob = 0.5;
  float* dE_dM;
  int niter = 500;
  int niter_terma = 3*n*n;
  int nT = 100;
  int niter_descorr = 2*n*n;
  int* sitiostest = malloc(niter*sizeof(int));
  float* T = malloc(nT*sizeof(float));
  float* energia = malloc(nT*sizeof(float));
  float* magnetizacion = malloc(nT*sizeof(float));
  float* energia_std = malloc(nT*sizeof(float));
  float* magnet_std = malloc(nT*sizeof(float));
  float* cv = malloc(nT*sizeof(float));
  float* E_terma = malloc(niter_terma*sizeof(float));
  float* M_terma = malloc(niter_terma*sizeof(float));
  float* magnet_corr = malloc(niter*sizeof(float));
  float energia_iter = 0.0;
  float magnetizacion_iter = 0.0;
  float energia_std_iter = 0.0;
  float magnet_std_iter = 0.0;
  float E_estado = 0.0;
  float M_estado = 0.0;
  float E1 = 0.0;
  float E2 = 0.0;
  float sumadevecinos = 0;
  float svm = 0.0;
  float* lut = malloc(12*sizeof(float)); // vector look up table
  float* s_ik = malloc(n*sizeof(float));

// Linspace de temperaturas
  float paso = 5.0/nT;
  *T = 0.001;
  for(i=1; i<nT-1; i++){
    *(T+i) = *(T+i-1) + paso;
  }

  srand(time(NULL));
  fill_lattice(lattice, n, 0.999);
  print_lattice(lattice, n);
  *energia = calc_energia(lattice, n, B, J);
  *magnetizacion = calc_magnet(lattice, n);
  E_estado = *energia;
  M_estado = *magnetizacion;
  // Inicializo vector de correlacion
  for(k=0; k<n; k++){
    *(s_ik+k) = 0.0;
  }

  // Comienzo iteración de temperaturas
  for(j=0; j<nT; j++){
    printf("Temperatura %d/%d\n", j, nT);
    energia_iter = 0.0;
    magnetizacion_iter = 0.0;
    E2 = 0.0;
    E1 = 0.0;
    // Armo el vector look up table
    for(i=0; i<5; i++){
      sumadevecinos = -4.0 + 2.0*i; // esto recupera -4, -2, 0, 2, 4
      *(lut+i) = expf(-(float)(-2*J* (sumadevecinos) - 2*B ) / *(T+j));  // tabla de exponenciales para s_i = -1
      *(lut+5+i) = expf(-(float)(2*J* (sumadevecinos) + 2*B ) / *(T+j));    // tabla de exponenciales para s_i = 1
      //printf("lut(%d) = %f, lut(%d), %f\n", i, *(lut+i), i+5, *(lut+5+i));
    }
    // Pretermalizo
    for(i=1; i<niter_terma; i++){
      dE_dM = metropolis(lattice, n, *(T+j), B, J, lut);
      //printf("Hice metropolis, i = %d/%d\n", i, niter_terma);
      E_estado += *dE_dM;
      M_estado += *(dE_dM+1);
      free(dE_dM);
      //printf("Metropolis i = %d/%d, E_estado = %f, M_estado = %f\n", i, niter_terma, E_estado, M_estado);
    }

    // Promedio estados a esa T
    for(i=1; i<niter; i++){
      // Avanzo niter_descorr para descorrelacionar
      for(k=0; k<niter_descorr; k++){
        dE_dM = metropolis(lattice, n, *(T+j), B, J, lut);
        //printf("Metropolis descorrelacionar k = %d/%d\n", k, niter_descorr);
        E_estado += *dE_dM;
        M_estado += *(dE_dM+1);
        free(dE_dM);
      }
      energia_iter += (E_estado)/(float)niter/(float)(n*n);
      energia_std_iter += (E_estado)*(E_estado)/(float)niter/(float)(n*n);
      magnetizacion_iter += (M_estado)/(float)niter/(float)(n*n);
      magnet_std_iter += (M_estado)*(M_estado)/(float)niter/(float)(n*n);
      E2 += (E_estado)*(E_estado);
      E1 += (E_estado);

      // Me quedo con los valores de una T para ver su correlación
      if(j==indice_T0){
        svm += (float)(*(lattice+n*4))/(float)niter; // para el s_valormedio promedio los valores que toma un spin particular
        *(magnet_corr+i) = calc_magnet(lattice, n);
        for(k=0; k<n; k++){
          //printf("s_i x s_i+k = %f\n",(float)(*(lattice+n*4) * *(lattice+n*4+k)));
          *(s_ik+k) += (float)(*(lattice+n*4) * *(lattice+n*4+k))/(float)niter; // para el s_i*s_i+k promedio los valores de cada producto
        }
      }
    }

//( E2/mcSteps - E1*E1/(mcSteps*mcSteps) )/(N*T[m]*T[m]); Bangho Aero x2

    // Guardo valores para cada T
    *(magnetizacion+j) = magnetizacion_iter;
    *(magnet_std+j) = (magnet_std_iter - magnetizacion_iter*magnetizacion_iter)/(float)niter;
    *(energia+j) = energia_iter;
    *(energia_std+j) = energia_std_iter- energia_iter*energia_iter;
    *(cv+j) = (E2/(float)niter - E1*E1/(float)niter/(float)niter)/(float)n/ *(T+j)/ *(T+j);
    //printf("E2 = %f, E1 = %f, cv = %f\n", E2, E1, *(cv+j));
  }

  //print_lattice(lattice, n);
  printf("Exportando...\n");
  exportar_vector_float(energia, nT, "energia.txt");
  exportar_vector_float(magnetizacion, nT, "magnetizacion.txt");
  exportar_vector_float(energia_std, nT, "energia_std.txt");
  exportar_vector_float(magnet_std, nT, "magnet_std.txt");
  exportar_vector_float(cv, nT, "cv.txt");
  exportar_vector_float(magnet_corr, niter, "magnet_corr.txt");

  return 0;
}
