#include "metropolis.h"
#include  "stdlib.h"
#include "math.h"
int metropolis(int *lattice, int n, float T) {
  int idx, out;
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

int flip(int *lattice, int n, float T, int idx) {
  int i, j, N, S, W, E, out;
  float dE, pi;
  i = (int)((float)idx/(float)n); // tomo parte entera de la division como numero de fila
  j = idx%n; // tomo resto de la division como numero de columna
  out = 0;
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
  dE = (float)(2* *(lattice+n*i+j) * (N+W+S+E));

  if(dE < 0){
    *(lattice+n*i+j) *= -10; // Flipeo el spin que me da idx
    out = 1;
  }
  else{
    pi = expf(-(float)dE / T);
    if((rand()/RAND_MAX)<pi){
      *(lattice+n*i+j) *= -10; // Flipeo el spin que me da idx
      out = 1;
    }
  }
  return out;
}
