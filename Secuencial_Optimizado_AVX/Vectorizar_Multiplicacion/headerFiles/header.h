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

#define SEED 10007
#define BASE 10
#define TAMLINHA 32

void inicializarQuaternions(__m256d **A, __m256d **B, double **DP, int N);

void calculos(__m256d *A, __m256d *B, double **DP, int N);

void destruir(__m256d *A, __m256d *B, double *DP);


#endif //HEADER_H
