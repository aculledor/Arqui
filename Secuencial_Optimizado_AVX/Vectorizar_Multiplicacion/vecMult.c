//
// Created by acu on 11/2/20.
//

#include "header.h"

void inicializarQuaternions(__m256d **A, __m256d **B, int N){
	(*A)  = (__m256d*)_mm_malloc(sizeof(__m256d)*N, TAMLINHA);
	(*B)  = (__m256d*)_mm_malloc(sizeof(__m256d)*N, TAMLINHA);
	

	for(int i=0;i<N;i++){
		(*A)[i] = _mm256_set_pd((double)rand(),(double)rand(),(double)rand(),(double)rand());
		(*B)[i] = _mm256_set_pd((double)rand(),(double)rand(),(double)rand(),(double)rand());
	} 
}

void calculos(__m256d *A, __m256d *B, double **DP, int N){
	__m256d aux = _mm256_setzero_pd();
	__m256d result = _mm256_setzero_pd();
	
	for(int i=0;i<N;i++){
		aux = _mm256_add_pd(
			A[i], 
			B[i] );
		result = _mm256_fmadd_pd(aux, aux, result);
	}
	
	(*DP) = (double *)&result;
}

void destruir(__m256d *A, __m256d *B, int N){
	_mm_free(A);
	_mm_free(B);
}

