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

void inicializarQuaternions(double ***A, double ***B, double **DP, int N);

void calculos(double **A, double **B, double **DP, int N);

void destruir(double **A, double **B, int N);


#endif //HEADER_H
