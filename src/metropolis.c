#include "metropolis.h"
#include  "stdlib.h"
#include "math.h"
int* metropolis(int *lattice, int n, float T) {
  int idx, *out;
  idx = pick_site(lattice, n);
  out = flip(lattice, n, T, idx);
  return out;
}



int pick_site(int *lattice, int n) {
  float x;
  int idx;
  x = (float)rand()/((float)RAND_MAX)*n*n; // Valor de distribución uniforme entre 0 y n^2
  idx = (int)x;
  return idx;
}



int* flip(int *lattice, int n, float T, int idx) {
  int i, j, N, S, W, E, dE, dM;
  float pi;
  int *dE_dM = malloc(2*sizeof(int));
  i = (int)((float)idx/(float)n); // tomo parte entera de la division como numero de fila
  j = idx%n; // tomo resto de la division como numero de columna


  // Condiciones de contorno

  if(j == n)
    E = *(lattice+n*i+j-n); // el de la derecha es el de la otra punta de la red
  else
    E = *(lattice+n*i+j+1);

  if(j == 0)
    W = *(lattice+n*i+j+n); // el de la izquierda es el de la otra punta de la red
  else
    W = *(lattice+n*i+j-1);

  if(i == 0)
    N = *(lattice+n*i+j+n*(n-1)); // el de arriba es el de más abajo
  else
    N = *(lattice+n*i+j-n);

  if(i == n)
    S = *(lattice+n*i+j-n*(n-1)); // el de abajo es el de más arriba
  else
    S = *(lattice+n*i+j+n);


  // Calculo el valor "pi" que me va a dar la probabilidad de aceptar el estado (flipeado el spin i,j)
  dE = (2* *(lattice+n*i+j) * (N+W+S+E));
  dM = 2* *(lattice+n*i+j);

  if(dE < 0){
    *(lattice+n*i+j) *= -1; // Flipeo el spin que me da idx
    *dE_dM = dE;
    *(dE_dM+1) = dM;
  }
  else{
    pi = expf(-(float)dE / T);
    if((rand()/RAND_MAX)<pi){
      *(lattice+n*i+j) *= -1; // Flipeo el spin que me da idx
      *dE_dM = dE;
      *(dE_dM+1) = dM;
    }
  }
  return dE_dM;
}

int calc_energia(int *lattice, int n) {
  int i, j, N, S, W, E, idx, energia;
  float dE, pi, out;
  energia = 0;
  for(idx = 0; idx<n*n; idx++){
    i = (int)((float)idx/(float)n); // tomo parte entera de la division como numero de fila
    j = idx%n; // tomo resto de la division como numero de columna
    out = 0.0;

    // Condiciones de contorno

    if(j == n)
      E = *(lattice+n*i+j-n); // el de la derecha es el de la otra punta de la red
    else
      E = *(lattice+n*i+j+1);

    if(j == 0)
      W = *(lattice+n*i+j+n); // el de la izquierda es el de la otra punta de la red
    else
      W = *(lattice+n*i+j-1);

    if(i == 0)
      N = *(lattice+n*i+j+n*(n-1)); // el de arriba es el de más abajo
    else
      N = *(lattice+n*i+j-n);

    if(i == n)
      S = *(lattice+n*i+j-n*(n-1)); // el de abajo es el de más arriba
    else
      S = *(lattice+n*i+j+n);

    // Sumo las interacciones con sur y este (porque en otra iteracion, el valor de la red sera sur y sera este de otro)
    energia += (*(lattice+n*i+j) * (S+E));
  }
  return energia;
}

int calc_magnet(int *lattice, int n) {
  int i, magnet;
  magnet = 0;
  for(i=0; i<n*n; i++){
    magnet += *(lattice+i);
  }
  return magnet;
}
