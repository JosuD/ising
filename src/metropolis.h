#ifndef METROPOLIS_H
#define METROPOLIS_H
float* metropolis(int *lattice, int n, float T, float B, float J, float *lut);
int pick_site(int *lattice, int n);
float* flip(int *lattice, int n, float T, int idx, float B, float J, float *lut);
float calc_energia(int *lattice, int n, float B, float J);
float calc_magnet(int *lattice, int n);

#endif
