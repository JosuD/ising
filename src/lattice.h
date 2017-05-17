#ifndef LATTICE_H
#define LATTICE_H
int fill_lattice(int *lattice, int n, float p);
int print_lattice(int *lattice, int n);
int randomspin(float p);
void exportar_vector_int(int *vector, int n, char* nombre);
#endif
