//
// Created by acu on 11/2/20.
//

#ifndef HEADER_H
#define HEADER_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pmmintrin.h>
#include <omp.h>

struct quaternion {
  double a;
  double b;
  double d;
  double c;
};

#define SEED 10007
#define BASE 10
#define TAMLINHA 32

void inicializarQuaternions(struct quaternion **A, struct quaternion **B, struct quaternion **sol, struct quaternion *DP, int N, int Fio);

void calculos(struct quaternion *A, struct quaternion *B, struct quaternion *sol, struct quaternion *DP, int N, int Fio);

void destruir(struct quaternion *A, struct quaternion *B, struct quaternion *sol);


#endif //HEADER_H
