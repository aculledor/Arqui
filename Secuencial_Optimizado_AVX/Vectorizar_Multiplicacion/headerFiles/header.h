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
#include <immintrin.h>

struct quaternion {
  double a;
  double b;
  double d;
  double c;
};

#define SEED 10007
#define BASE 10
#define TAMLINHA 32


void calculos(__m256d *A, __m256d *B, __m256d *DP, int N);

void destruir(__m256d *A, __m256d *B);


#endif //HEADER_H
